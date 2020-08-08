#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED

typedef struct Node Node;

struct Node {
    int g;
    int h;
    int f;

    int x;
    int y;

    int numero;

    int parent;
    Node* suivant;
};

typedef struct{
    Node *firstNode;
}NodeArray;

#endif // PATHFINDING_H_INCLUDED
