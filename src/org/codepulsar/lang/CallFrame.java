package org.codepulsar.lang;

import org.codepulsar.lang.variables.FunctionVariable;

public class CallFrame {
    private final String caller;
    private final int returnIP;

    private final FunctionVariable.Function function;
    private final int stackOffset;

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
