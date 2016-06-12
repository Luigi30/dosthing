#ifndef BLASTER_HPP
#define BLASTER_HPP

#include <i86.h>
#include <conio.h>

class SoundBlaster {
    //I/O 220, IRQ 5, DMA 1 by default in Dosbox
    int baseAddress;
    int resetPort;
    int readPort;
    int writePort;
    int readBufferPort;
    
    public:
    SoundBlaster(int _base){
        baseAddress = _base;
        resetPort   = baseAddress + 0x06;
        readPort    = baseAddress + 0x0A;
        writePort   = baseAddress + 0x0C;
        readBufferPort = baseAddress + 0x0E;
    }
    
    bool reset(){
        outp(resetPort, 0x01);
        delay(1); //1ms sleep - only doing this during init so this should be ok
        outp(resetPort, 0x00);
        delay(1); //1ms sleep
        unsigned char data = inp(readPort);
        return data == 0xAA;
    }
};

#endif