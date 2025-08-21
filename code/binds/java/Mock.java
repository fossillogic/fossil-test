// FossilMock.java
package com.fossil;

public class FossilMock {

    static {
        System.loadLibrary("fossil_mock");
    }

    private long nativeHandle; // pointer to fossil_mock_calllist_t

    public FossilMock() {
        nativeHandle = init();
    }

    private native long init();
    public native void destroy();
    public native void addCall(String functionName, long args, int numArgs);
    public native void print();
}
