// FossilSanity.java
package com.fossil;

public class FossilSanity {

    static {
        System.loadLibrary("fossil_sanity");
    }

    public static native int execute(String command);
    public static native int pid();
    public static native void sleep(int ms);
    public static native boolean fileExists(String path);
    public static native int createFile(String path);
    public static native int deleteFile(String path);
    public static native String readFile(String path);
    public static native int writeFile(String path, String data);
    public static native boolean dirExists(String path);
    public static native int createDir(String path);
    public static native String getEnv(String name);
    public static native int setEnv(String name, String value);
    public static native String timestamp();
    public static native long uptimeMs();
    public static native boolean isRunning(int pid);
    public static native boolean kill(int pid);
}
