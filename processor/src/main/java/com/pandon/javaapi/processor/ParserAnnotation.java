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
import java.util.Locale;
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
                    System.out.println("JNIClass<JNIMethod>: type = " + e.asType());
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
                                    method.overloadSN(),
                                    e.asType().toString()));
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
                            pkgName,
                            e.getSimpleName().toString(),
                            field.sign(),
                            e.asType().toString());
                    classInfo.addFieldInfo(fieldInfo);
                    if (!fieldInfo.includes.isEmpty()) {
                        packInfo.addInclude(fieldInfo.includes);
                    }
                    if (!fieldInfo.preDefined.isEmpty()) {
                        packInfo.addPreDefined(fieldInfo.preDefined);
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

                    packInfo.classes.sort((info1, info2) ->
                            info1.simpleName.compareToIgnoreCase(info2.simpleName));

                    for (JniClassInfo.ClassInfo classInfo : packInfo.classes) {

                        classInfo.methods.sort((info1, info2) ->
                                info1.name.compareToIgnoreCase(info2.name));
                        classInfo.fields.sort((info1, info2) ->
                                info1.name.compareToIgnoreCase(info2.name));

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
            String[] _pkg = newPkgName.split("_");
            String initSpace = "";

            StringBuilder macro_sb = new StringBuilder();
            StringBuilder method_code_sb = new StringBuilder();
            StringBuilder obj_convert_sb = new StringBuilder();
            StringBuilder field_code_enum_sb = new StringBuilder();
            StringBuilder field_struct_sb = new StringBuilder();

            for (JniClassInfo.ClassInfo cInfo : packInfo.classes) {
                String simpleName = cInfo.simpleName.replace(".", "_");

                String _initSpace1 = getSpaceStr(1, initSpace);

                if (!cInfo.fields.isEmpty()) {
                    macro_sb.append(String.format(Constants.Format.MACRO_JAVA_BEAN,
                                    simpleName, cInfo.className));

                    String _initSpace2 = getSpaceStr(1, _initSpace1);

                    obj_convert_sb.append("\n")
                            .append(String.format(Constants.Format.TRANSFORM_CLASS_HEADER,
                                    simpleName, simpleName))
                            .append(" {\n")
                            .append(_initSpace1).append(Constants.Format.TRANSFORM_USING)
                            .append(_initSpace1).append(Constants.Format.TRANSFORM_PUBLIC)
                            .append(_initSpace2)
                            .append(String.format(Constants.Format.TRANSFORM_METHOD_EXTRACT, simpleName))
                            .append(_initSpace2)
                            .append(String.format(Constants.Format.TRANSFORM_METHOD_CONVERT, simpleName))
                            .append(initSpace)
                            .append("};\n");

                    field_code_enum_sb
                            .append("\n")
                            .append(initSpace)
                            .append(String.format(Constants.Format.ENUM_CLASS_HEADER, simpleName))
                            .append(" {\n");

                    field_struct_sb
                            .append("\n")
                            .append(initSpace)
                            .append("struct ")
                            .append(simpleName)
                            .append(" {\n");

                    for (JniClassInfo.FieldInfo fInfo : cInfo.fields) {
                        field_struct_sb.append(_initSpace1)
                                .append(fInfo.type)
                                .append(" ")
                                .append(fInfo.name)
                                .append(";\n");

                        field_code_enum_sb.append(_initSpace1)
                                .append(fInfo.name)
                                .append(" = ")
                                .append(fInfo.id)
                                .append(",\n");
                    }

                    field_struct_sb.append(initSpace).append("};\n");

                    field_code_enum_sb.append(initSpace).append("};\n");
                }

                for (JniClassInfo.MethodInfo mInfo : cInfo.methods) {
                    method_code_sb.append("\n")
                            .append(String.format(Constants.Format.METHOD_CODE_ANNOTATION,
                                    mInfo.sign, mInfo.isStaticMethod, mInfo.isNonvirtualMethod))
                            .append(_initSpace1)
                            .append(String.format(Locale.getDefault(), Constants.Format.METHOD_CODE,
                                    simpleName, mInfo.name, mInfo.overloadSN, mInfo.id));
                }
            }

            StringBuilder content_sb = new StringBuilder();
            content_sb.append("\n")
                    .append(initSpace)
                    .append(String.format(Constants.Format.MACRO_JSON_FILE,
                            newPkgName.toUpperCase(), newPkgName));
            if (macro_sb.length() > 0) {
                content_sb.append("\n").append(macro_sb);
            }

            if (obj_convert_sb.length() > 0) {
                content_sb.append("\n")
                        .append(initSpace)
                        .append(Constants.Format.NAME_SPACE_TEMPLATE);
            }

            if (packInfo.preDefined.size() > 0) {
                content_sb.append("\n");
                for (String preDefined : packInfo.preDefined) {
                    content_sb.append(initSpace).append(preDefined);
                }
            }
            content_sb.append(field_struct_sb);
            content_sb.append(obj_convert_sb);
            content_sb.append(field_code_enum_sb);
            if (method_code_sb.length() > 0) {
                content_sb.append("\n")
                        .append(initSpace)
                        .append(String.format(Constants.Format.METHOD_CODE_HEADER,
                                newPkgName.toUpperCase()));
                content_sb.append(method_code_sb);
                content_sb.append(initSpace).append("};\n");
            }

            String macro = "JNI_" + newPkgName.toUpperCase() + "_H";
            StringBuilder header_sb = new StringBuilder();
            header_sb.append("#ifndef ").append(macro).append("\n");
            header_sb.append("#define ").append(macro).append("\n");

            if (packInfo.includes.size() > 0) {
                header_sb.append("\n");
                for (String include : packInfo.includes) {
                    header_sb.append(include);
                }
            }

            header_sb.append("\n");
            for (String s : _pkg) {
                header_sb.append(String.format(Constants.Format.NAME_SPACE, s.toUpperCase()));
            }

            header_sb.append(content_sb);

            header_sb.append("\n");
            for (int i = _pkg.length - 1; i >= 0; i--) {
                header_sb
                        .append("} // namespace ")
                        .append(_pkg[i].toUpperCase())
                        .append("\n");
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

    private String getSpaceStr(int number, String initSpace) {
        if (number > 0) {
            return getSpaceStr(--number, initSpace + "    ");
        }
        return initSpace;
    }
}
