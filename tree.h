//
// Created by mllau on 2/14/2025.
//

#ifndef TREE_H
#define TREE_H



#include "Node.h"
#include <vector>


class tree {
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* CheckBalance();
    int max;
    Node* Balance(Node* temp);
    Node* insertHelp(Node* temp, std::string Name, int ID);


public:
    Node* root;
    tree();
    std::vector<Node*> storage;
    //std::queue<Node*> temp;
    Node* insert(Node* temp, std::string name, int ID);
    std::string insert( std::string name, int ID);

    std::string remove(int ID);
    std::string search(int ID);
    std::string search(std::string Name);
    std::string printInOrder();
    std::string printPreOrder();
    std::string printPostOrder();
    std::string printLevelCount();
    std::string removeInOrder(int N);
    Node* getNode(int ID);
};



#endif //TREE_H
