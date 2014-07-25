#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>

#include "compress.h"

void showHelpMe(){
    qDebug("|-------|Huffman Compressor Help|-------|");
    qDebug("|---------------------------------------|");
    qDebug(" -c 'file'  // Compress file.");
    qDebug(" -c 'file' -o 'outname.huff'' // Compress file with different name.");
    qDebug("|---------------------------------------|");
    qDebug(" file.huff // Descompress file.");
    qDebug(" file.huff -d 'outpath' // Descompress file with different outpath");
    qDebug("|---------------------------------------|");
}

int main(int argc, char *argv[])
{

    QString a;
    a = argv[1];
    QString b;
    b = argv[2];
    QString c;
    c = argv[3];
    QString d;
    d = argv[4];



    if(argc <= 6){
        if(a=="-h"){
            showHelpMe();
        }

        //Compression Standart.
        else if(a == "-c"){
            //Compression with different path of output file.
            if(c == "-o"){
                if(d.contains(".huff")){
                    Compress huff = Compress(b,d);
                    huff.encode();
                } else {
                    qDebug() << "Invalid command. Type -h to get help.";
                }
            } else {
                Compress huff = Compress(b,"out.huff");
                huff.encode();
            }

        }
        //Descompression with different path of output file.
        else if(a.contains(".huff")){
            if(b=="-d"){
                Compress huff = Compress(a,c);
                huff.decode();
            } else {
                Compress huff = Compress(a,"");
                huff.decode();
            }
        } else {
            qDebug() << "Invalid command. Type -h to get help.";
        }
    }

    else {
        qDebug() << "Invalid command. Type -h to get help.";
    }

    return 0;
}

