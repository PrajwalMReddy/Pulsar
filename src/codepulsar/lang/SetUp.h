#ifndef CODEPULSAR_SETUP_H
#define CODEPULSAR_SETUP_H

#include <iostream>

using namespace std;


struct SetUp {
    string fileIn;
    bool debug;
    string version;
};

extern SetUp setUpConditions;

#endif
