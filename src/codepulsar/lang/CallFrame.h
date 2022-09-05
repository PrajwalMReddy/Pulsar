#ifndef CODEPULSAR_CALLFRAME_H
#define CODEPULSAR_CALLFRAME_H

#include <string>

#include "../variable/FunctionVariable.h"


namespace Pulsar {
    class CallFrame {
        public:
            CallFrame(std::string caller, int returnIP, Pulsar::FunctionVariable* function, int stackOffset);

            std::string getCaller();
            int getReturnIP();
            int getStackOffset();

        private:
            std::string caller;
            int returnIP;

            FunctionVariable* function;
            int stackOffset;
    };
}


#endif
