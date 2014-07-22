#ifndef QUEUE_H
#define QUEUE_H

#include <Node.h>

class Queue {
private:
    void operator = (const Queue&) {}
    Queue(const Queue&) {}
public:
    Queue ();
    void clear();
    void enqueue(Node * node);
    Node * dequeue();
    Node * frontValue();
    int length();
private:
    Node * m_base;
    int m_count;
};

#endif // QUEUE_H
