#include "compress.h"
#include "QDebug"

Compress::Compress(QString path)
{
    this->setFile(path);
    this->setName(path);
    this->setPath(path);
}

void Compress::setFile(QString path){
    QFile file(path);

    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        this->file = data ;
        qDebug() << data.size();
    }
    else{
        qDebug() << path;
        qDebug() << "Error: Could not open the file.";
    }
}

void Compress::setName(QString name){
    for(int i = name.length() -1; i > 0; i--)
        if(name.at(i) == '/'){
            name.remove(0, i + 1);
            break;
        }
    this->fileName = name;
}

void Compress::setPath(QString path){
    this->filePath = path;
}

void Compress::showInput(){
    if(this->file != NULL)
        qDebug() << this->file;
    else
        qDebug() << "Error: Could not find the input file.";
}

QByteArray Compress::getFile(){
    if(this->file != NULL)
        return this->file;
    else
        qDebug() << "Error: Could not find the input file.";
}

QString fill(QString bin, int n){
    int size = bin.size();
    if(size > n)
        qDebug() << "Warning: Overflow.";
    for(int i=0; i< n - size; i++)
        bin.prepend('0');
    return bin;
}

int Compress::make(){
    QByteArray file = this->getFile();
    Frequency frequecy = Frequency(file);
    Huffman huff(frequecy);

    QByteArray tree;
    tree.append(huff.getTree()->createRep());
    int treeSize = tree.size();

    QString name = this->fileName;

    qDebug() << "Compressing:" << name;

    QString encoded;

    for(int i = 0; i < file.size(); i++){
            unsigned char c = file.at(i);
            encoded.append(huff.getHash()->value(c));
    }

    int garbageSize = 8 - encoded.size() % 8;

    for(int i = 0; i < garbageSize ; i++)
        encoded.append('0');

    bool convert;
    QByteArray encodedChar;
    for(int i = 0; i < encoded.length(); i+= 8){
            QString bin = encoded.mid(i,8);
            unsigned char c = bin.toInt(&convert,2);
            encodedChar.append(c);
    }

    QString garbageSizeToBit = fill(QString::number(garbageSize,10),3);
    QString treeSizeToBit = fill(QString::number(treeSize,10),13);
    QString nameSizeToBit = fill(QString::number(name.size(),10),8);

    QByteArray compressed;
    compressed.append(garbageSizeToBit);
    compressed.append(treeSizeToBit);
    compressed.append(nameSizeToBit);
    compressed.append(name);
    compressed.append(tree);
    compressed.append(encodedChar);

    QFile out("out.huff");
    out.resize(0);
    out.open(QIODevice::ReadWrite);
    out.write(compressed);
    out.close();

    return 0;
}

int Compress::extract(){
    QByteArray file = this->getFile();
    qDebug() << "Descompactando:" << this->fileName;

    bool convert;
    int garbageSize = file.mid(0,3).toInt(&convert,10);
    int treeSize = file.mid(3,13).toInt(&convert,10);
    int nameSize = file.mid(16,8).toInt(&convert,10);

    QString name = file.mid(24,nameSize);
    QString tree = file.mid(24 + nameSize, treeSize);


    Tree * tr = new Tree(tree);

    QString contentBin;

    for(int i = 24 + nameSize + treeSize; i < file.size(); i++){
        unsigned char c = file.at(i);
        int decimal = c;
        contentBin.append(fill(QString::number(decimal,2),8));
    }

    QByteArray decoded;
    Node * n = tr->root();


    for(int i = 0; i <= contentBin.size()-garbageSize; i++) {
        if (n->isLeaf()) {
            decoded.append(n->key());
            n = tr->root();
            i--;
        }
        else {
            if (contentBin.at(i) == '0') {
                n = n->left();
            }
            else if (contentBin.at(i) == '1') {
                n = n->right();
            }
            else {
                qDebug() << "Error: File corrupted";
            }
        }
    }

    qDebug() << decoded.size();
    QFile out(name);
    out.resize(0);
    out.open(QIODevice::ReadWrite);
    out.write(decoded);
    out.close();

    return 0;
}
