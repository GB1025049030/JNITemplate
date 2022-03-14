package com.pandon.javaapi.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Retention(RetentionPolicy.SOURCE)
@Target(ElementType.METHOD)
public @interface JNIMethod {
    /**
     * method signature
     */
    String sign();

    boolean isStaticMethod() default false;

    /**
     * JNI need call 'CallNonvirtual<Type>Method', eg. CallNonvirtualVoidMethod
     */
    boolean isNonvirtualMethod() default false;

    /**
     * Unique serial number identifying overloaded method.
     * The default value is 1, and non-overloaded methods use the default value
     */
    int overloadSN() default 1;
}
