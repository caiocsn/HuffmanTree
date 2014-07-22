#include "huffman.h"
#include "QDebug"

Huffman::Huffman(Frequency freq)
{
    this->frequency = freq;
    this->tree = this->makeHuffman();
    dictionary = new QHash<unsigned char, QString>;
    this->makeHash();
    //this->showHash();
}

Huffman::Huffman(Tree *t){
    this->setTree(t);
    dictionary = new QHash<unsigned char, QString>;
    this->makeHash();
}

Tree * Huffman::makeHuffman(){
    QList<Node*> * list;
    Node * root;
    list = this->frequency.getList();
    while(list->length() != 1){
        this->frequency.sort();
        Node * aux1 = list->at(0);
        Node * aux2 = list->at(1);
        list->removeFirst();
        list->removeFirst();
        Node * aux3 = new Node;
        aux3->setFrequency(aux1->frequency() + aux2->frequency());
        aux3->setLeft(aux1);
        aux3->setRight(aux2);
        list->append(aux3);
        root = aux3;
    }
    Tree * t = new Tree;
    t->setRoot(root);
    int h = t->setHeight(root);
    root->setHeight(h);
    return t;
}

void Huffman::setTree(Tree *t){
    this->tree = t;
}

Tree * Huffman::getTree(){
    return this->tree;
}

void Huffman::addNodeToHash(Node *node, QString path){
    if(node->isLeaf())
        inserIntoHash(node->key(),path);
    else{

    if(node->left()){
        QString path = node->path();
        path.append("0");
        node->left()->setPath(path);
        addNodeToHash(node->left(),node->left()->path());
    }
    if(node->right()){
        QString path = node->path();
        path.append("1");
        node->right()->setPath(path);
        addNodeToHash(node->right(),node->right()->path());
    }
    }

}

void Huffman::inserIntoHash(unsigned char key, QString path){
    this->dictionary->insert(key,path);
}

void Huffman::makeHash(){
    addNodeToHash(this->tree->root(),"");
}

void Huffman::showHash(){
    QList<unsigned char> keys = dictionary->keys();
        for (int i = 0; i < keys.size(); ++i)
            qDebug() << keys[i] << ":" << dictionary->value(keys[i]);
}

QHash<unsigned char, QString> * Huffman::getHash(){
    if(this->dictionary!= NULL)
        return this->dictionary;
    else
        qDebug() << "Error: Can't get a valid hash";
}
