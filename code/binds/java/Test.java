// FossilPizzaEngine.java
package com.fossil;

public class FossilPizzaEngine {

    static {
        System.loadLibrary("fossil_pizza"); // Load the JNI shared library
    }

    private long nativeHandle; // pointer to fossil_pizza_engine_t

    public FossilPizzaEngine(String[] args) {
        nativeHandle = init(args);
    }

    private native long init(String[] args);
    public native boolean addSuite(long suite);
    public native boolean addCase(long suite, long testCase);
    public native boolean runSuite(long suite);
    public native boolean runAll();
    public native void summary();
    public native boolean end();
}
