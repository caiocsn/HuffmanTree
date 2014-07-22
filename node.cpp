# include <QDebug>
# include <node.h>

Node::Node() {
    m_left = 0;
    m_right = 0;
    m_root = 0;
    m_frequency = 0;
    m_key = 0;
    m_next = 0;
    m_height = 0;
    m_path = "";
}


Node::Node(unsigned char key, int frequency) {
    m_left = 0;
    m_right = 0;
    m_root = 0;
    m_frequency = frequency;
    m_key = key;
    m_next = 0;
    m_height = 0;
    m_path = "";

}

Node::Node(unsigned char key) {
    this->m_left = 0;
    this->m_right = 0;
    this->m_root = 0;
    this->m_height = 0;
    this->m_key = key;
    m_path = "";
}

Node::Node(QChar key) {
    QVariant v = key;
    bool ok;
    this->m_left = 0;
    this->m_right = 0;
    this->m_root = 0;
    this->m_height = 0;
    this->m_key = v.toInt(&ok);
    m_path = "";
}



Node::~Node() {
    m_left = 0;
    m_right = 0;
    m_root = 0;
    m_frequency = 0;
    m_key = 0;
    m_next = 0;
    m_height = 0;
    m_path = "";
}


void Node::setRoot(Node *root) {
    this->m_root = root;
}

Node * Node::root() {
    return m_root;
}

void Node::setLeft(Node *left) {
    this->m_left = left;
    int h = m_height;
    h++;
    m_left->setHeight(h);
}

Node * Node::left() {
    return m_left;
}


void Node::setRight(Node *right) {
    this->m_right = right;
    int h = m_height;
    h++;
    m_right->setHeight(h);
}

Node * Node::right() {
    return m_right;
}

void Node::setFrequency(int freq) {
    m_frequency = freq;
}

int Node::frequency() {
    return m_frequency;
}

void Node::setKey(char key) {
    m_key = key;
}

unsigned char Node::key() {
    return m_key;
}

bool Node::isLeaf() {
    if (left() || right()) {
        return false;
    } else {
        return true;
    }

}

void Node::setNext(Node *node)
{
    m_next = node;
}

Node *Node::next()
{
    return m_next;
}

void Node::setHeight(int height) {
    int h = height - 1;
    if (left()) left()->setHeight(h);
    if (right()) right()->setHeight(h);
    m_height = height;
}

int Node::height() {
    return m_height;
}

void Node::setPath(QString path) {
    m_path = path;
}

QString Node::path() {
    return m_path;
}
