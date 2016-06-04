#include <stdio.h>
#include <stdlib.h>
#include <cstring>

struct PCXHeader {
    unsigned char manufacturer;
    unsigned char version;
    unsigned char encoding;
    unsigned char bitsPerPixel;
    int XMin;
    int YMin;
    int XMax;
    int YMax;
    int vertDPI;
    unsigned char palette[48];
    unsigned char reserved;
    unsigned char colorPlanes;
    int bytesPerLine;
    int paletteType;
    int HScrSize;
    int VScrSize;
    unsigned char filler[56];
};

class PCX {
    PCXHeader header;
    unsigned char *data;
    int validateHeader();
    void readHeader(unsigned char*);
    void decode();

    unsigned char *pixelData;

    public:
    PCX(char *filename);
    ~PCX();
    PCXHeader getHeader();
    unsigned char* getPixelData();

    int getSizeX();
    int getSizeY();
};
