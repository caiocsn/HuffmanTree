# include <QChar>
# include <QDebug>
# include <Tree.h>
# include <QString>

Tree::Tree() {
    m_root = 0;
    m_rep = "";
}

Tree::Tree(Node * root) {
    m_root = root;
}

void Tree::verifyChar(QString characters, Node * root) {
    QChar character = characters.at(0);
    QVariant v = character;
    bool ok;

    unsigned char character1 = v.toInt(&ok);


    if (character1 == '(') {
        Node * node = new Node();
        node->setRoot(root);
        QString nodePath = root->path();

        if (root->left() == 0) {
            nodePath.append("0");
            root->setLeft(node);
            node->setPath(nodePath);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, node);
            }

        } else {
            nodePath.append("1");
            root->setRight(node);
            node->setPath(nodePath);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, node);
            }
        }
    } else {

        if (character == ')') {

            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, root->root());
            }

        } else {

            Node * node = new Node(character1);
            node->setRoot(root);
            QString nodePath = root->path();

            if (character1 == '/') {
                QChar character2 = characters.at(1);
                v = character2;
                bool ok;
                unsigned char character3 = v.toInt(&ok);

                node->setKey(character3);
                characters.remove(0,1);
            }

            if (root->left() == 0) {
                nodePath.append("0");
                root->setLeft(node);
                node->setPath(nodePath);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                    verifyChar(characters, root);
                }

            } else {
                nodePath.append("1");
                root->setRight(node);
                node->setPath(nodePath);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                    verifyChar(characters, root);
                }
            }
        }

    }

}

Tree::Tree (QString rep) {
    m_rep = rep;
    Node * root =  new Node();
    verifyChar(rep, root);
    m_root = root;
}

Tree::~Tree () {
    delete m_root;
    m_rep = "";
}

void Tree::showTree() {
    preOrder(m_root);
}

QString Tree::createRep () {
    m_rep = "";
    preOrderRep(m_root);
    return m_rep;
}

Node * Tree::root() {
    return m_root;
}

void Tree::setRoot (Node * newRoot) {
    m_root = newRoot;
}

QString Tree::rep () {
    createRep();
    return m_rep;

}

int Tree::setHeight(Node * node) {
    if (!node) return -1;
    return 1 + max(setHeight(node->left()), setHeight(node->right()));
}

void Tree::preOrder(Node *node) {
    if (node) {
        preOrder(node->left());
        this->visit(node);
        preOrder(node->right());
    }
}

void Tree::visit(Node *node) {
    QString str = "";
    if (node->key() != 0) {
        str.append(node->key());
    } else {
        str.append("[]");
    }
    for(int i = 0; i < node->height(); ++i) {
        str.prepend("\t");
    }
    qDebug() << str;
}


void Tree::preOrderRep(Node *node) {
    if (node) {
        if (node->left() && !node->left()->isLeaf()) m_rep.append("(");
        preOrderRep(node->left());
        if (node->left() && !node->left()->isLeaf()) m_rep.append(")");

        if (node->key() != 0) {
            if(node->key() == '(' || node->key() == ')' || node->key() == '/') {
                m_rep.append('/');
            }
            m_rep.append(node->key());
        }

        if (node->right() && !node->right()->isLeaf()) m_rep.append("(");
        preOrderRep(node->right());
        if (node->right() && !node->right()->isLeaf()) m_rep.append(")");
    }
}

int Tree::max(int n1, int n2)
{
    if (n1 > n2) return n1;
    else return n2;
}
