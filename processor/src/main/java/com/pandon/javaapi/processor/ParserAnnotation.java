package com.pandon.javaapi.processor;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.serializer.SerializerFeature;
import com.google.auto.service.AutoService;
import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;
import com.pandon.javaapi.annotation.JNIMethod;
import com.pandon.javaapi.processor.Constants.MethodFlag;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.function.Consumer;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.Element;
import javax.lang.model.element.ElementKind;
import javax.lang.model.element.TypeElement;

@AutoService(Processor.class)
public final class ParserAnnotation extends AbstractProcessor {
    private static final String OBJECT_CONFIG_DIR = "javaapiconfigs/";
    private static final String OBJECT_HEADER_DIR = "javaapiheaders/";

    @Override
    public synchronized void init(ProcessingEnvironment processingEnv) {
        super.init(processingEnv);
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        Set<String> annotations = new LinkedHashSet<>();
        annotations.add(JNIClass.class.getCanonicalName());
        return annotations;
    }

    @Override
    public Set<String> getSupportedOptions() {
        return super.getSupportedOptions();
    }

    @Override
    public SourceVersion getSupportedSourceVersion() {
        return SourceVersion.latestSupported();
    }

    @Override
    public boolean process(Set<? extends TypeElement> set, RoundEnvironment roundEnvironment) {
        if (roundEnvironment.processingOver()) {
            return false;
        }

        System.out.println("process: " + roundEnvironment);

        Set<? extends Element> elements = roundEnvironment
                .getElementsAnnotatedWith(JNIClass.class);
        if (elements == null || elements.isEmpty()) {
            return true;
        }
        JniClassInfo jniClassInfo = new JniClassInfo();
        elements.forEach((Consumer<Element>) element -> {
            String pkgName = element.getEnclosingElement().toString();
            List<? extends Element> list = element.getEnclosedElements();

            JniClassInfo.PackInfo packInfo;
            if (jniClassInfo.mPkgInfos.containsKey(pkgName)) {
                packInfo = jniClassInfo.mPkgInfos.get(pkgName);
            } else {
                packInfo = new JniClassInfo.PackInfo();
                jniClassInfo.mPkgInfos.put(pkgName, packInfo);
            }

            JniClassInfo.ClassInfo classInfo = new JniClassInfo.ClassInfo(pkgName,
                    element.getSimpleName().toString());
            packInfo.addClassInfo(classInfo);

            for (Element e : list) {
                ElementKind ek = e.getKind();
                if (ek == ElementKind.CONSTRUCTOR) {
                    System.out.println("JNIClass<Constructor>: " + e);
                } else if (ek == ElementKind.METHOD) {
                    System.out.println("JNIClass<JNIMethod>: " + e);
                    JNIMethod method = e.getAnnotation(JNIMethod.class);
                    if (method == null) {
                        continue;
                    }
                    if (method.isStaticMethod() && method.isNonvirtualMethod()) {
                        throw new IllegalArgumentException("You can only choose one of 'isStaticMethod'" +
                                " and 'isNonvirtualMethod' in the annotation");
                    }
                    int flag = 0;
                    if (method.isStaticMethod()) {
                        flag |= MethodFlag.FLAG_JNI_METHOD_IS_STATIC;
                    }
                    if (method.isNonvirtualMethod()) {
                        flag |= MethodFlag.FLAG_JNI_METHOD_IS_NONVIRTUAL;
                    }
                    boolean ret = classInfo.addMethodInfo(
                            new JniClassInfo.MethodInfo(
                                    e.getSimpleName().toString(),
                                    method.sign(),
                                    flag,
                                    method.overloadSN()));
                    if (!ret) {
                        String className = pkgName + "." + element.getSimpleName().toString();
                        throw new IllegalArgumentException("The annotation(overloadSN = "
                                + method.overloadSN() + ") in the '"
                                + className + "$" + e.getSimpleName().toString() + "' is exist");
                    }
                } else if (ek.isField()) {
                    System.out.println("JNIClass<Field>: Name: " + e.getSimpleName()
                            + ", Type: " + e.asType());
                    JNIField field = e.getAnnotation(JNIField.class);
                    if (field == null) {
                        continue;
                    }
                    JniClassInfo.FieldInfo fieldInfo = new JniClassInfo.FieldInfo(
                            e.getSimpleName().toString(),
                            field.sign(),
                            e.asType().toString());
                    classInfo.addFieldInfo(fieldInfo);
                    if (!fieldInfo.includes.isEmpty()) {
                        packInfo.addIncludes(fieldInfo.includes);
                    }
                }
            }
        });
        if (!jniClassInfo.mPkgInfos.isEmpty()) {
            List<String> keys = new ArrayList<>(jniClassInfo.mPkgInfos.keySet());
            Collections.sort(keys);
            keys.forEach(key -> {
                int methodId = 0;
                int fieldId = 0;
                JniClassInfo.PackInfo packInfo = jniClassInfo.mPkgInfos.get(key);
                if (packInfo != null && !packInfo.classes.isEmpty()) {
                    for (JniClassInfo.ClassInfo classInfo : packInfo.classes) {
                        for (JniClassInfo.MethodInfo methodInfo : classInfo.methods) {
                            methodInfo.setMethodId(++methodId);
                        }
                        for (JniClassInfo.FieldInfo fieldInfo : classInfo.fields) {
                            fieldInfo.setFieldId(++fieldId);
                        }
                    }
                }
            });

            writeConfigs(jniClassInfo);
            writeHeaders(jniClassInfo);
        }
        writeMethodFlagEnum();
        return false;
    }

    private void writeConfigs(JniClassInfo data) {
        String path;
        for (String pkgName : data.mPkgInfos.keySet()) {
            JniClassInfo.PackInfo packInfo = data.mPkgInfos.get(pkgName);
            path = OBJECT_CONFIG_DIR + pkgName.replace(".", "_") + ".json";
            JSONObject object = JSONObject.parseObject(JSONObject.toJSONString(packInfo));
            String jsonStr = JSON.toJSONString(object,
                    SerializerFeature.PrettyFormat,
                    SerializerFeature.WriteMapNullValue,
                    SerializerFeature.WriteNullStringAsEmpty,
                    SerializerFeature.WriteNullNumberAsZero,
                    SerializerFeature.WriteNullBooleanAsFalse,
                    SerializerFeature.WriteNullListAsEmpty,
                    SerializerFeature.WriteDateUseDateFormat)
                    .replaceAll("\t", "  ");

            writeToFile(jsonStr, path);
        }
    }

    private void writeHeaders(JniClassInfo data) {
        for (String pkgName : data.mPkgInfos.keySet()) {
            JniClassInfo.PackInfo packInfo = data.mPkgInfos.get(pkgName);
            if (packInfo.classes.isEmpty()) {
                continue;
            }

            String newPkgName = pkgName.replace(".", "_");
            String macro = "JNI_" + newPkgName.toUpperCase() + "_H";
            StringBuilder header_sb = new StringBuilder();
            header_sb.append("#ifndef ").append(macro).append("\n");
            header_sb.append("#define ").append(macro).append("\n");

            if (packInfo.includes.size() > 0) {
                header_sb.append("\n");
            }
            for (String include : packInfo.includes) {
                header_sb.append(include).append("\n");
            }

            header_sb.append("\n");
            header_sb.append("#define ")
                    .append("JSON_CONFIG_FILE_")
                    .append(newPkgName.toUpperCase())
                    .append(" \"")
                    .append(newPkgName)
                    .append(".json\"\n");
            header_sb.append("\n");

            for (JniClassInfo.ClassInfo classInfo : packInfo.classes) {
                String simpleName = classInfo.simpleName.replace(".", "_");
                if (!classInfo.fields.isEmpty()) {
                    StringBuilder field_code_enum_sb = new StringBuilder();
                    field_code_enum_sb.append("enum class ")
                            .append(simpleName)
                            .append("_FIELD_CODE")
                            .append(" {\n");

                    StringBuilder field_struct_sb = new StringBuilder();
                    field_struct_sb.append("struct ")
                            .append(simpleName)
                            .append(" {\n");
                    for (JniClassInfo.FieldInfo fieldInfo : classInfo.fields) {
                        field_struct_sb.append("    ")
                                .append(fieldInfo.type)
                                .append(" ")
                                .append(fieldInfo.name)
                                .append(";\n");

                        field_code_enum_sb.append("    ")
                                .append(fieldInfo.name)
                                .append(" = ")
                                .append(fieldInfo.id)
                                .append(",\n");
                    }
                    field_struct_sb.append("};\n");
                    field_struct_sb.append("\n");

                    field_struct_sb.append(String.format(Constants.METHOD_C2J_FORMAT,
                            simpleName, simpleName)).append("\n");
                    field_struct_sb.append(String.format(Constants.METHOD_J2C_FORMAT,
                            simpleName, simpleName)).append("\n");
                    field_struct_sb.append("\n");

                    field_code_enum_sb.append("};\n");

                    header_sb.append(field_struct_sb);
                    header_sb.append(field_code_enum_sb);
                }

                if (!classInfo.methods.isEmpty()) {
                    StringBuilder method_code_sb = new StringBuilder();
                    method_code_sb.append("enum class MethodCode_")
                            .append(newPkgName.toUpperCase())
                            .append(" {\n");
                    for (JniClassInfo.MethodInfo methodInfo : classInfo.methods) {
                        method_code_sb.append("    ")
                                .append("// sign: ")
                                .append(methodInfo.sign)
                                .append("\n")
                                .append("    ")
                                .append(simpleName)
                                .append("_")
                                .append(methodInfo.name)
                                .append("_")
                                .append(methodInfo.overloadSN)
                                .append(" = ")
                                .append(methodInfo.id).append(",\n");
                    }
                    method_code_sb.append("};\n");

                    header_sb.append(method_code_sb);
                }
            }

            header_sb.append("\n");
            header_sb.append("#endif //").append(macro).append("\n");

            writeToFile(header_sb.toString(), OBJECT_HEADER_DIR + newPkgName.toLowerCase() + ".h");
        }
    }

    private void writeMethodFlagEnum() {
        StringBuilder sb = new StringBuilder();
        sb.append("#ifndef JNI_METHOD_FLAG_H\n");
        sb.append("#define JNI_METHOD_FLAG_H\n");
        sb.append("\n");

        sb.append("enum class MethodFlag {\n");
        Field[] fields = MethodFlag.class.getFields();
        try {
            for (Field field : fields) {
                sb.append("    ")
                        .append(field.getName())
                        .append(" = ")
                        .append(field.getInt(MethodFlag.class))
                        .append(",\n");
            }
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
        sb.append("};\n");
        sb.append("\n");
        sb.append("#endif //JNI_METHOD_FLAG_H\n");
        String code = sb.toString();

        writeToFile(code, OBJECT_HEADER_DIR + "jni_method_flag.h");
    }

    private void writeToFile(String fileContent, String filePath) {
        try {
            if (checkAndCreatePath(filePath)) {
                FileWriter fileWriter = new FileWriter(filePath);
                fileWriter.write(fileContent);
                fileWriter.close();
            } else {
                System.out.println("Error: create " + filePath + " failed!!!");
            }
        } catch (IOException e) {
            System.out.println("Error: write " + filePath + " failed!!!");
        }
    }

    private boolean checkAndCreatePath(String path) throws IOException {
        File config = new File(path);
        if (!config.getParentFile().exists()) {
            return config.getParentFile().mkdirs() && config.createNewFile();
        }
        if (!config.exists()) {
            return config.createNewFile();
        }
        return true;
    }
}
