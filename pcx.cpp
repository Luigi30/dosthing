/*
    The PCX format is a relatively simple format
    that provides a minimum of compression using
    Run Length Encoding (RLE).
*/

#include "pcx.hpp"

PCX::PCX(char *filename){
    FILE *pcxFile;
    pcxFile = fopen(filename, "rb");

    unsigned char buffer[128];

    if(pcxFile != NULL){
        fread(buffer, sizeof(buffer), 1, pcxFile);
        //printf("Read file into buffer...\n");

        readHeader(buffer);

        if(!validateHeader()){
            printf("%s isn't a PCX file: Invalid header!", filename);
        }

        //printf("OK, PCX file has %d bytes per line\n", header.bytesPerLine);

        //Now read the remaining length minus 768 bytes (the palette) in
        data = (unsigned char*)malloc(header.bytesPerLine * getSizeY());
        fread(data, header.bytesPerLine, getSizeY(), pcxFile);
        pixelData = NULL;
        
    } else {
        printf("%s isn't a readable file!", filename);
        exit(255);
    }
}

PCX::~PCX(){
    free(data);
    free(pixelData);
}

int PCX::validateHeader(){
    //printf("Attempting to validate header...\n");
    
    if(header.manufacturer != 0x0A) return 0;
    if(header.encoding != 0x01) return 0;
    if(header.bitsPerPixel > 8) {
        printf("Can only render 8bpp PCXes!");
        return 0;
    }

    return 1;
}

PCXHeader PCX::getHeader(){
    return header;
}

int PCX::getSizeX(){
    return header.XMax - header.XMin; //some need this + 2???
}

int PCX::getSizeY(){
    return header.YMax - header.YMin; //some need this + 2???
}

void PCX::readHeader(unsigned char *buffer){
        header.manufacturer = buffer[0];
        header.version = buffer[1];
        header.encoding = buffer[2];
        header.bitsPerPixel = buffer[3];
        header.XMin = buffer[4] | buffer[5] << 8;
        header.YMin = buffer[6] | buffer[7] << 8;
        header.XMax = buffer[8] | buffer[9] << 8;
        header.YMax = buffer[10] | buffer[11] << 8;
        header.vertDPI = buffer[12] | buffer[13] << 8;
        std::memcpy(&header.palette, &buffer[14], 48);
        header.reserved = buffer[62];
        header.colorPlanes = buffer[63];
        header.bytesPerLine = buffer[64] | buffer[65] << 8;
        header.paletteType = buffer[66] | buffer[67] << 8;
        header.HScrSize = buffer[68] | buffer[69] << 8;
        header.VScrSize = buffer[70] | buffer[71] << 8;
        std::memcpy(&header.filler, &buffer[72], 56);
        header.HScrSize = getSizeX() + 1;
        header.VScrSize = getSizeY() + 1;

        //printf("Read header...\n");
}

unsigned char* PCX::getPixelData(){
        //printf("getPixelData()\n");
        
    if(pixelData == NULL){
        //printf("Generating pixel data\n");
        //pixelData = (unsigned char*)malloc(header.bytesPerLine * header.VScrSize);
        pixelData = (unsigned char*)malloc(header.HScrSize * header.VScrSize);
        std::memset(pixelData, 0, header.HScrSize * header.VScrSize);
        //printf("%d", header.bytesPerLine);

        int remainingLength = 0;
        int currentColor = 0;
        int pixelLocation = 0;
        long encodedOffset = 0;

        //how many bytes total is the image?
        long totalSize = header.HScrSize * header.VScrSize;
                
                //printf("%d, %d dimensions", header.HScrSize, header.VScrSize);

                for(int pixelLocation=0;pixelLocation<totalSize;pixelLocation++){       
                        if(remainingLength == 0){
                                //printf("Reading offset %d\n", encodedOffset);
                                //is the next byte length or color?
                                if(data[encodedOffset] >= 192) {
                                        //length
                                        remainingLength = (data[encodedOffset] & ~(0xC0)); //set two high bits to 0, that's the length
                                        encodedOffset++;
                                        currentColor = data[encodedOffset]; //and the next byte is color
                                        
                                        //printf("(%x %x) = Found length %d, color %d\n", data[encodedOffset-1], data[encodedOffset], remainingLength, currentColor);
                                } else {
                                        //color
                                        currentColor = data[encodedOffset];
                                        remainingLength = 1; //length 1
                                        //printf("(%x) = Found length 1, color %d\n", data[encodedOffset], currentColor);
                                }
                                
                                encodedOffset++;
                        }
                        
                        //process the current pixel
                        pixelData[pixelLocation] = currentColor;
                        remainingLength--;
                }

    } else {
                //printf("Retrieving pixel data without generation\n");
        }

    return pixelData;
}
