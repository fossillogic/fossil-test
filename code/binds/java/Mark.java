// FossilBenchmark.java
package com.fossil;

public class FossilBenchmark {

    static {
        System.loadLibrary("fossil_benchmark");
    }

    private long nativeHandle; // pointer to fossil_mark_t

    public FossilBenchmark(String name) {
        nativeHandle = init(name);
    }

    private native long init(String name);
    public native void start();
    public native void stop();
    public native double elapsed();
    public native double min();
    public native double max();
    public native double avg();
    public native void reset();
    public native void report();
}
