//
// Created by mllau on 2/14/2025.
//

#ifndef NODE_H
#define NODE_H

#include "student.h"


class Node {
public:
    Node(Node* parent, student* value, int h);
    Node(student* value);

    student* Value;
    Node* Parent;
    Node* left;
    Node* right;
    int Height; // Top Down height
    int BHeight; //Bottum Up height

    Node* Add(int side, Node* instance);
    Node* Add(int side, student* value);
    Node* GetChild(int side);
};



#endif //NODE_H
