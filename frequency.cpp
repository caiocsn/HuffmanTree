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
