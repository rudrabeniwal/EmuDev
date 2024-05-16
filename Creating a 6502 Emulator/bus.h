#pragma once 
#include <stdint.h>
class Bus{

public:
    virtual uint8_t read (uint16_t address, bool sync = false) = 0;

};