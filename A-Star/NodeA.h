#include <stdio.h>

class Node
{
    public:
    Node();
    Node(int, int);
    bool visited;
    int x, y;
    float f, g, h;
    Node* parent;
    void print();
    void calculatefn();
    bool operator< (const Node& other);
    bool operator> (const Node& other);
    bool operator== (const Node& other);
    bool operator>= (const Node& other);
    bool operator<= (const Node& other);
    bool operator!= (const Node& other);
    Node& operator= (const Node& other);
};

Node::Node()
{
    visited = false;
    x = 0;
    y = 0;
    f = 0;
    g = 0;
    h = 0;
    parent = NULL;
}

Node::Node(int m_x, int m_y)
{
    x = m_x;
    y = m_y;
    g = 0.0;
    h = 0.0;
    f = 0.0;
    visited = false;
}


void Node::calculatefn()
{
    f = g + h;
}

void Node::print()
{
    printf("%d %d\n", x, y);
}

bool Node::operator< (const Node& other)
{
    return this->f > other.f;
}

bool Node::operator> (const Node& other)
{
    return this->f < other.f;
}

bool Node::operator== (const Node& other)
{
    return (this->x == other.x && this->y == other.y);
}

bool Node::operator>= (const Node& other)
{
    if(this->f < other.f)
        return true;
    else if(this->f == other.f)
        return true;
    else
        return false;
}

bool Node::operator<= (const Node& other)
{
    if(this->f > other.f)
        return true;
    else if (this->f == other.f)
        return true;
    else
        return false;
}

bool Node::operator!= (const Node& other)
{
    return !(this->x == other.x && this->y == other.y);
}

Node& Node::operator= (const Node& other)
{
    f = other.f;
    g = other.g;
    h = other.h;
    x = other.x;
    y = other.y;
    visited = other.visited;

    //
    parent = new Node;
    parent = other.parent;
}
