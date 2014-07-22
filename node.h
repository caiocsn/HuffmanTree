#ifndef NODE_H
#define NODE_H
# include <QChar>
# include <QString>
# include <QVariant>

class Node {
public:
    Node ();
    Node (unsigned char key, int frequency);
    Node (unsigned char key);
    Node (QChar key);
    ~Node ();
    void setRoot (Node * root);
    Node * root();
    void setLeft (Node * left);
    Node * left();
    void setRight (Node * right);
    Node * right();
    void setFrequency(int frequency);
    int frequency();
    void setKey(char key);
    unsigned char key();
    bool isLeaf();
    void setNext(Node * node);
    Node * next();
    void setHeight(int height);
    int height();
    void setPath(QString path);
    QString path();
private:
    Node * m_root;
    Node * m_left;
    Node * m_right;
    Node * m_next;
    unsigned char m_key;
    int m_frequency;
    int m_height;
    QString m_path;
};

#endif // NODE_H
