## 编译

使用 Android Studio 进行编译，编译完成之后会在当前工程 javaapiconfigs 和 javaapiheaders 目录下
生成相关的 json 文件和头文件

***注：*** javaapiconfigs 和 javaapiheaders 均为源码路径下的软连接

## 添加 Java Api

1. 在名为 "javaApi" 的 module 中添加同名 java 文件（同包名，同类名），
   将需要新增的 api 复制到该文件中，方法体可以为空。如下：

```
public class TestNewApi {
    public void testNewApi(String value){
        // 空实现
    }
}

```

2. 新增 JAVA API 需要添加注解，主要分两步：

- 该类添加注解```@JNIClass```，该注解无需赋值
- 为需要处理的全局变量和方法分别添加注解 ```@JNIField``` 和 ```@JNIMethod```

```@JNIField``` 注解需要赋值变量的签名信息以供 Native 层解析使用

```
@JNIClass
public class AbilityMissionInfo {
    @JNIField(sign = "Lohos/bundle/base/ElementName;")
    private ElementName mAbilityBaseBundleName;
    @JNIField(sign = "I")
    private int mAbilityMissionId;
}
```

```@JNIMethod```，其中包含以下值：

- sign：方法签名，例如：```(Ljava/lang/String;)V```
- isStaticMethod：否是静态方法，默认为 false
- isNonvirtualMethod：表示否是需要使用到 nonvirtual 模式的方法，默认为 false
- overloadSN: 为了区分重载方法，默认值为 1，重载方法则需要设置，并确保唯一

```
@JNIClass
public class TestNewApi {
    @JNIMethod(sign = "(Ljava/lang/String;)V",
            overloadSN = 1) // overloadSN 默认值为 1，可以不写 overloadSN = 1
    public void testNewApi(String value) {
        // 空实现
    }

    @JNIMethod(sign = "(Ljava/lang/String;)V",
            overloadSN = 2) // 重载方法, 必须填写 overloadSN = xxx
    public void testNewApi(boolean value){
        // 空实现
    }
}
```

## Java Api 限制

为了便于 JNI 调用，Java api 中的复杂参数限定为只能使用数组，
例如 Map 结构修改为两个一维数组，Set、List 等修改为一个一维数组

```
// 原始 api
public void setData(Map<String, Integer> value) {
  ...
}

// 修改后的 api，以供 JNI 调用
public void setData(String[] keys, int[] values) {
  Map<String, Integer> data = new HashMap<>();
  for (int i = 0; i < keys.length; i++) {
    data.put(keys.get(i), values.get(i));
  }
  setData(data);
}
```

## 查看 Java api 签名信息

1. Api 添加完之后先进行编译一次
2. Use the "javap -s" command to view the signature information of the added api

```
javap -s javaApi/build/classes/java/main/com/pandon/javaapi/simple/TestJavaApi.class

// 输出信息如下:
Compiled from "TestJavaApi.java"
public class com.pandon.javaapi.simple.TestJavaApi {
  public com.pandon.javaapi.simple.TestJavaApi();
    descriptor: ()V

  public void setValues(java.lang.String[], boolean);
    descriptor: ([Ljava/lang/String;Z)V

  public com.pandon.javaapi.simple.TestJavaApi$Data setValues();
    descriptor: ()Lcom/pandon/javaapi/simple/TestJavaApi$Data;

  public static int getValues(int);
    descriptor: (I)I
}
```

***注：*** 最好是通过此方式获取签名信息，再将其填写到注解中，避免手写有遗漏或是错误