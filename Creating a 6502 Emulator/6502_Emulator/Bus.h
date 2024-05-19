#pragma once 
#include <stdint.h>

using Addr = uint16_t;

class Bus{

public:
    virtual uint8_t read (Addr address, bool sync = false) = 0;
    virtual uint8_t write (Addr address, uint8_t ) = 0;

};