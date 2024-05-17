#pragma once 
#include <stdint.h>

using Addr = uint16_t;

class Bus{

public:
    virtual uint8_t read (uint16_t address, bool sync = false) = 0;

};