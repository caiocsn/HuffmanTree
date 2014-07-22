#ifndef FREQUENCY_H
#define FREQUENCY_H
#include "QList"
#include "QByteArray"
#include "node.h"

class Frequency
{
private:
    int * frequency;
    QByteArray input;
    QList<Node*> * frequencyList;
public:
    Frequency(){}
    Frequency(QByteArray file);
    // Imprime a frequencia dos caracteres na tela
    void showFrequency();
    // Ordena a lista de acordo com a frequencia de cada elemento
    void sort();
    // Retorna a lista com a frenquecia dos caracteres
    QList<Node*> * getList();
private:
    // Seta o arquivo
    void setFile(QByteArray file);
    // Seta o array de frequencia
    void setFrequecy();
    // Cria a lista com os nós e suas determinadas frequencias
    void makeList();
};

#endif // FREQUENCY_H
