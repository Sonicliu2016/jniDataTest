package com.sonic.jnidemo1;

/**
 * Created by Administrator on 2017/12/9 0009.
 */

public class JniUtil {
    static {
        System.loadLibrary("jni_lib");
    }

    public native String getStringFromJni();

    public native int getSum(int x,int y);

    public native String getNewStr(String str);

    public native int[] bubbleSort(int[] arr);

}
