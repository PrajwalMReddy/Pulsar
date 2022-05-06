package org.codepulsar.lang;

import org.codepulsar.lang.variables.FunctionVariable;

public class CallFrame {
    private String caller;
    private int returnIP;

    private FunctionVariable.Function function;
    private int stackOffset;

    public CallFrame(String caller, int returnIP, FunctionVariable.Function function, int stackOffset) {
        this.caller = caller;
        this.returnIP = returnIP;
        this.function = function;
        this.stackOffset = stackOffset;
    }

    public String getCaller() {
        return this.caller;
    }

    public int getReturnIP() {
        return this.returnIP;
    }

    public int getStackOffset() {
        return this.stackOffset;
    }
}
