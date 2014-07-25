#ifndef COMPRESS_H
#define COMPRESS_H
#include "QString"
#include "QFile"
#include "QTextStream"
#include "QChar"
#include "frequency.h"
#include "huffman.h"
#include "QTextStream"

class Compress
{
private:
    QString fileName;
    QString filePath;
    QString outputName;
    QByteArray file;
public:
    Compress(){}
    Compress(QString path, QString output);
    // Imprime o arquivo de input
    void showInput();
    // Retorna o arquivo de input
    QByteArray getFile();
    // Comprime o arquivo
    int encode();
    // Extrai o arquivo
    int decode();
private:
    // Seta o arquivo de entrada
    void setFile(QString path);
    // Seta o nome do arquivo
    void setName(QString name);
    // Seta o caminho do arquivo
    void setPath(QString path);
};

#endif // COMPRESS_H
