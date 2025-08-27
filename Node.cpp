//
// Created by mllau on 2/14/2025.
//

#include "Node.h"

Node::Node(Node* parent, student* value, int h){
    this->Parent = parent;
    this->Value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->Height = h;
    this->BHeight=1;
}

Node::Node(student* Value) {
    this->Parent = nullptr;
    this->Value = Value;
    this->left = nullptr;
    this->right = nullptr;
    this->BHeight = 1;

}

Node* Node::Add(int side, Node* instance) {
    if (side == 0) {
        this->left = instance;
    } else {
        this->right = instance;
    }
    return instance;
}



