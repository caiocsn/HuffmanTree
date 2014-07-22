#include "frequency.h"
#include "QDebug"
#include <QtAlgorithms>

Frequency::Frequency(QByteArray file)
{
    this->setFile(file);
    this->setFrequecy();
    this->makeList();
    this->sort();
    //this->showFrequency();
}

Frequency::Frequency(int a, QByteArray freq){
    this->decodeArray(freq);
    this->makeList();
    this->sort();
}

void Frequency::setFile(QByteArray file){
    if(file!= NULL)
    this->input = file;
    else
        qDebug() << "Error: Could not find the input file.";
}

void Frequency::setFrequecy(){
    if(this->input != NULL){
        int * aux;
        aux = new int[256];

        for(int i = 0; i < 256 ; i++)
            aux[i] = 0;

        for(int i = 0; i<this->input.size() ; i++){
            unsigned char c = input.at(i);
            aux[c] ++;
        }
        this->frequency = aux;
    }

    else
        qDebug() << "Error: Could not find the input file.";
}

void Frequency::showFrequency(){
    if(!this->frequencyList->empty()){
        for(int i = 0; i< this->frequencyList->size(); i++){
            Node *aux = this->frequencyList->at(i);
            int key = aux->key();
            int freq = aux->frequency();
            qDebug() << key << ":" << freq;
        }
    }
    else
        qDebug() << "Error: The frequency list is empy.";
}

void Frequency::makeList(){
    if(this->frequency != NULL){
        this->frequencyList = new QList<Node*>;
        for(int i = 0; i < 256; i++)
            if(this->frequency[i] > 0){
                unsigned char aux = i;
                this->frequencyList->append(new Node(aux,this->frequency[i]));
            }
    }
}

bool dtcomp(Node *left, Node *right){
  return left->frequency() < right->frequency();
}

void Frequency::sort(){
  qSort(this->frequencyList->begin(),this->frequencyList->end(),dtcomp);
}

QList<Node*> *Frequency::getList(){
    return this->frequencyList;
}

QString Frequency::fill(QString bin, int n){
    int size = bin.size();
    if(size > n)
        qDebug() << "Warning: Overflow.";
    for(int i=0; i< n - size; i++)
        bin.prepend('0');
    return bin;
}

QByteArray Frequency::encondeArray(){
    QByteArray aux;
    for(int i = 0; i < 256; i++){
        if(this->frequency[i] >0 ){
        bool convert;
        QString bin = fill(QString::number(this->frequency[i],2),24);
        unsigned char n1 = bin.mid(0,8).toInt(&convert,2);
        unsigned char n2 = bin.mid(8,8).toInt(&convert,2);
        unsigned char n3 = bin.mid(16,8).toInt(&convert,2);
        aux.append(i);
        aux.append(n1);
        aux.append(n2);
        aux.append(n3);
        }
    }
    return aux;
}

void Frequency::decodeArray(QByteArray array){
    int * aux = new int[256];

    for(int i = 0; i < 256 ; i++)
        aux[i] = 0;

    for(int i = 0; i< array.size(); i+=4){
        bool convert;
        unsigned char index = array.at(i);
        unsigned char n1 = array.at(i+1);
        unsigned char n2 = array.at(i + 2);
        unsigned char n3 = array.at(i + 3);
        QString bin = fill(QString::number(n1,2),8);
        bin.append(fill(QString::number(n2,2),8));
        bin.append(fill(QString::number(n3,2),8));
        int freq = bin.toInt(&convert,2);
        aux[index] = freq;
    }
    this->frequency = aux;

}
