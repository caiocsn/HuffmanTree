#include "QDebug"
#include "compress.h"

int main(){
    Compress teste = Compress("C:/Qt/MaintenanceTool.exe");
    teste.encode();
    Compress teste1 = Compress("C:/Users/Caio/Documents/QtProjects/build-HuffmanTree-Desktop_Qt_5_3_MinGW_32bit-Debug/out.huff");
    teste1.decode();

}
