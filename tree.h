#ifndef TREE_H
#define TREE_H

# include <QString>
# include <node.h>
# include <QVariant>

class Tree {
public:
    Tree();
    Tree(Node * root);
    Tree(QString rep);
    ~Tree();
    void showTree();
    QString createRep ();
    Node * root();
    void setRoot (Node * newRoot);
    QString rep ();
    int setHeight(Node * node);
private:
    void preOrder(Node * node);
    void visit(Node * node);
    void preOrderRep(Node * node);
    int max(int n1, int n2);
    void visitRep(Node * node);
    void verifyChar(QString characters, Node * root);
private:
    Node * m_root;
    QString m_rep;
};

#endif // TREE_H
