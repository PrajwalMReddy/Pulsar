#include "CallFrame.h"


Pulsar::CallFrame::CallFrame(std::string caller, int returnIP, Pulsar::FunctionVariable function, int stackOffset) : function(function) {
    this->caller = caller;
    this->returnIP = returnIP;
    this->function = function;
    this->stackOffset = stackOffset;
}

std::string Pulsar::CallFrame::getCaller() {
    return this->caller;
}

int Pulsar::CallFrame::getReturnIP() {
    return this->returnIP;
}

int Pulsar::CallFrame::getStackOffset() {
    return this->stackOffset;
}
