#ifndef CODEPULSAR_SETUP_H
#define CODEPULSAR_SETUP_H

#include <string>


namespace Pulsar {
    struct SetUp {
        std::string fileIn;
        bool debug;
        std::string version;
    };

    SetUp conditions = {"", false, "0.1.0"};
}

#endif
