#include <Queue.h>
#include <QDebug>

Queue::Queue() {
    m_count = 0;
    m_base = 0;
}

void Queue:: clear() {
    Node * current = m_base;
    for (int i = 0; i < m_count; ++i) {
        Node * aux = current->next();
        delete current;
        current = aux;
        delete aux;
    }
    m_count = 0;
}

void Queue:: enqueue(Node * node) {
    if(m_base) {
        Node * aux = m_base;
        while  (aux->next() && aux->frequency() < node->frequency()) {
            aux = aux->next();
        }
        node->setNext(aux->next());
        aux->setNext(node);
    } else {
        m_base = node;
    }
    ++m_count;
}

Node * Queue:: dequeue() {
    Node * aux = new Node(m_base->key(), m_base->frequency());
    aux->setNext(m_base->next());
    m_base = m_base->next();
    --m_count;
    return aux;
}

Node * Queue::frontValue()
{
    return m_base;
}

int Queue::length()
{
    return m_count;
}
