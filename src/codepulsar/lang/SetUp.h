#ifndef CODEPULSAR_SETUP_H
#define CODEPULSAR_SETUP_H

#include <string>


namespace Pulsar {
    struct SetUp {
        std::string fileIn;
        bool debug;
        std::string version;
    };
}

extern Pulsar::SetUp conditions;


#endif
