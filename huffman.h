#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "QHash"
#include "tree.h"
#include "frequency.h"
#include "QString"

class Huffman
{
private:
    Tree * tree;
    Frequency frequency;
    QHash<unsigned char, QString> * dictionary;
public:
    Huffman(){}
    Huffman(Frequency freq);
    // Seta a árvore a ser utilizada
    void setTree(Tree * t);
    // Retorna a árvore
    Tree * getTree();
    // Inicializa o dicionário
    void makeHash();
    // Imprime o dicionário
    void showHash();
    // Retorna o dicionário
    QHash<unsigned char, QString> * getHash();
private:
    // Gera a árvore de Huffman
    Tree * makeHuffman();
    // Adiciona os nós e seus respectivos caminhos ao dicionário
    void addNodeToHash(Node * node, QString path);
    // Insere key/caminho  na hash
    void inserIntoHash(unsigned char key, QString path);
};

#endif // HUFFMAN_H
