//
// Created by mllau on 2/14/2025.
//

#include "tree.h"
#include <sstream>
#include <algorithm>

//#include "catch2/internal/catch_test_spec_parser.hpp"

tree::tree() {
    max=0;
    root=nullptr;
}

int HeightGetter(Node* temp) { //O(1)
    //If node isn't real, return 0
    if(temp==nullptr) {
        return 0;
    }
    return temp->BHeight; //If it is, return the height.
}




Node* tree::Balance(Node* temp) {//O(1)


    //If stuff doesn't exist, the value is 0.
    int Balancing = 0;
    int HeightLL=0;
    int HeightLR=0;
    int HeightRR=0;
    int HeightRL=0;

    if(temp) { //This value is real. Accounts for existence
        Balancing = HeightGetter(temp->left) - HeightGetter(temp->right); //Get height difference between sides.

        if(temp->left!=nullptr) {
            // Left side
            HeightLL=HeightGetter(temp->left->left);
            HeightLR=HeightGetter(temp->left->right);
        }
        if(temp->right!=nullptr) {
            // Right Side
            HeightRR=HeightGetter(temp->right->right);
            HeightRL=HeightGetter(temp->right->left);
        }
    }


    //Balancing used to determine if rotation even needed. If so, find difference in grandchildren.
    if(Balancing > 1 && (HeightLL-HeightLR)>=0) { //Rotate Right
        //Left Left longer than Left Right
        return rotateRight(temp);
    }

    if(Balancing < -1 && (HeightRL-HeightRR)<=0) { //Rotate Left
        //Right Left smaller than Right Right
        return rotateLeft(temp);
    }

    if(Balancing > 1 && (HeightLL-HeightLR)<0) { //Left Rotate then Right
        //Left Left smaller than Left Right
        temp-> left = rotateLeft(temp->left);
        return rotateRight(temp);
    }

    if(Balancing < -1 && (HeightRL-HeightRR)>0) { //Right Heavy
        //Right Left bigger than Right Right
        temp-> right = rotateRight(temp->right);
        return rotateLeft(temp);
    }


    return temp;
}

//Final Insert function
//Used while loop instead of recursion because of the need for the func to return a string.
std::string tree::insert(std::string name, int ID) { //O(log(n))
    // ID size
    /*if(std::to_string(ID).length()!=8) {
        return "unsuccessful";
    }*/

    // Duplicates
    if(!storage.empty()) {
        for(Node* item: storage) {
            if(item->Value->ID == ID) {
                return "unsuccessful";
            }
        }
    }

    // String Letters are Values
    for(char letter: name) {
        if(!(('A'<=letter and letter<='Z') or ('a'<=letter and letter<='z') or letter==' ')) {
            return "unsuccessful";
        }
    }

    //Empty Tree; plant the root.
    if (root == nullptr) {
        Node* temp = new Node(nullptr, new student(name, ID), 1);
        root = temp;
        storage.push_back(temp);
        return "successful";
    }


    Node* current= root;
    Node* previous=nullptr;

    //Get move down until you reach the end. Navigate with your ID value
    while(current) {
        previous=current;
        if (ID<current->Value->ID) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    //Make the node exist on the correct side of the parent.
    if (ID<previous->Value->ID) {
        current=new Node(previous, new student(name, ID), previous->Height+1);
        previous->left = current;
        //A surprise tool for later.
        if(current->Height+1>max){max=current->Height+1;}
        storage.push_back(current);
    } else{
        current=new Node(previous, new student(name, ID), previous->Height+1);
        previous->right = current;
        //A surprise tool for later.
        if(current->Height+1>max){max=current->Height+1;}
        storage.push_back(current);

    }
    Node* backup;
    //Start at the bottom, and move up the chain.
    //Check each potentially affected node for any rotations
    while(current) { //Root has no parent. Will go to null and end process
        current->BHeight= std::max(HeightGetter(current->left), HeightGetter(current->right)) + 1; //Gonna need that height for this.
        current = Balance(current); //Balance if needed
        //Need to reconnect with parent.
        if(current->Parent && current->Parent->Value->ID>current->Value->ID) {
            current->Parent->left= current;
        } else if (current->Parent){
            current->Parent->right= current;
        }
        backup=current; //Surprise tool
        current=current->Parent;//Move up
    }
    root=backup; //Top with parent null is new root.
    return "successful";
}; //on F, explodes.

std::string tree::remove(int ID) { //O(log(N))
    //Issue w/ children
    bool goingDown = false;
    Node* current= root;
    int count = 0;
    if(storage.empty()) {
        return "unsuccessful"; //Empty; can't remove anything
    }

    if(storage.size()==1 && root->Value->ID==ID) { //One thing, and it's the target.
        storage.pop_back();
        Node* former = root;
        root=nullptr;
        delete former;
        return "successful";
    }
    if(storage.size()==1) { //Save some time if there's one thing and it isn't the target.
        return "unsuccessful";
    }

    for(Node* item: storage) {
        if(item->Value->ID == ID) {
            storage.erase(storage.begin()+count);
            goingDown = true; //Ah, so it does exist. kill it then.
            break;
        }
        count+=1;
    }
    if(!goingDown) {
        return "unsuccessful"; //Does not exist bc we didn't find it in storage vector
    }
    if (root->Value->ID==ID) { //Root is the target.
        Node* former = root;
        if(HeightGetter(former->left)>HeightGetter(former->right)) { //Which side takes priority in succession
            root=former->left; //Replace
            root->Parent = nullptr; //Orphan the root
            root->right=former->right; // Connect the ENTIRE RIGHT SIDE to the root
            delete former; //Gone
        } else if(HeightGetter(former->left)<=HeightGetter(former->right)) {
            //Same but opposite side
            root=former->right;
            root->Parent = nullptr;
            root->left = former->left;
            delete former;
        }

        return "successful"; //Leave
    }



    while(current!=nullptr) { //Our item exists.
        if(current->Value->ID == ID) { //Found it.
            Node* former = current;
            if(former->left == nullptr && former->right == nullptr) { //Leaf
                if(former->Parent->left == former) {
                    former->Parent->left=nullptr; //Removes child pointer
                } else {
                    former->Parent->right=nullptr;
                }
                current==nullptr;
                delete former; //No other links to cut.
            }else if(HeightGetter(former->left)>=HeightGetter(former->right)) { //Children exist, figure out succession then delete.
                current=former->left;
                current->Parent = former->Parent;
                former->Parent=nullptr;
                current->Parent->left=current;
                current->right=former->right;
                delete former;
            } else {
                //Opposite side
                current=former->right;
                current->Parent = former->Parent;
                former->Parent=nullptr;
                current->Parent->right=current;
                current->left = former->left;
                delete former;
            }

            return "successful";
        }
        //Follow the dotted line.
        if(ID<current->Value->ID){
            current = current->left;
        } else if (ID>current->Value->ID) {
            current = current->right;
        }

    }
    //Erm... we didn't find the target (current is nullptr)
    //So return unsuccessful
    return "unsuccessful";
};

//Because it's an AVL tree, just use ID to find the spot ez.
std::string tree::search(int ID) { //O(log(N))
    Node* current= root;
    while(current) {
        if(current->Value->ID == ID) {
            return current->Value->Name;
        }
        if(ID<current->Value->ID) {
            current = current->left;
        } else {
            current = current->right;
        }

    }
    return "unsuccessful";
};

//Unelegant but functional. Go through the stored list, get the values, sort, and send.
std::string tree::search(std::string Name) {//O(nlog(n)) Because of std::sort
    std::vector <std::string> result;
    for(Node* item: storage) {
        if (item->Value->Name == Name) {
            result.push_back(std::to_string(item->Value->ID));
        }
    }

    if(result.empty()) {
        return "unsuccessful";
    }

    sort(result.begin(), result.end()); //O(nlog(n))

    std::string compiledResult = "";

    for (std::string instance: result) {
        compiledResult += instance + "\n"; //Line for each.
    }

    return compiledResult;
};

//Left
//Center
//Right

//Splitter and commaSpam are here to format what will be printed.
std::vector<std::string> splitter(std::string &s, char delim) {
    std::vector<std::string> temp;
    std::stringstream Thing(s);
    std::string Item;
    while (getline(Thing, Item, delim)) {
        temp.push_back(Item);
    }
    return temp;
}

std::string commaSpam(std::string input) {
    std::vector<std::string> split = splitter(input, ',');
    std::string result = "";
    for(int i = 0; i < split.size()-1; i++) {
        if(split[i]!="," && split[i]!="") {
            result += split[i] + ", ";
        }
    }
    //Last without comma
    if(split.back()!="," && split.back()!="") {
        result += split.back();
    }
    //For an extra weird thing caused by empties after the final real value
    if(result.back()==',' or result.back()==' ') {
        return result.substr(0, result.size()-2);
    }

    return result;

}

//All of the prints are similar, just have different orders of recursion.
//Helpers do the recursion work so the main func can return a string. Makes testing easier.
//Essentially, move down as the type of order dictates.
//Uses comma to make distance, as it allows for names with a space "John Jones" to be maintained.
std::string PrintOrderHelp(Node* side) { //O(N)
    std::string Total;
    if(!side) {
        return "";
    }

    if(side->left!=nullptr) {
        Total+=PrintOrderHelp(side->left)+",";
    }

    Total+=side->Value->Name + ",";

    if(side->right!=nullptr) {
        Total+=PrintOrderHelp(side->right) +",";
    }

    return Total;
}
std::string tree::printInOrder() {//O(N)

    if(root==nullptr){
        return "";
    }

    std::string final="";
    final += PrintOrderHelp(root->left)+",";
    final += root->Value->Name + ",";
    final += PrintOrderHelp(root->right)+",";

    return commaSpam(final);

}

//Same but different order.
std::string PrintPreOrderHelp(Node* side) { //O(N)
    std::string Total;

    Total+=side->Value->Name +",";

    if(side->left!=nullptr) {
        Total+=PrintPreOrderHelp(side->left)+",";
    }

    if(side->right!=nullptr) {
        Total+=PrintPreOrderHelp(side->right)+",";
    }

    return Total;
}
std::string tree::printPreOrder() { //O(N)
    std::string Total; //Yikes

    Node* current = root;

    Total+=current->Value->Name +",";

    if(current->left!=nullptr) { //Bottom first.
        Total+=PrintPreOrderHelp(current->left)+",";
    }

    if(current->right!=nullptr) {
        Total+=PrintPreOrderHelp(current->right)+",";
    }



    return commaSpam(Total);
};

//Same
std::string PrintPostOrderHelp(Node* side) { //O(N)
    std::string Total;

    if(side->left!=nullptr) { //Bottom first.
        Total+=PrintPostOrderHelp(side->left)+",";
    }

    if(side->right!=nullptr) {
        Total+=PrintPostOrderHelp(side->right)+",";
    }

    Total+=side->Value->Name+",";

    return Total;
}
std::string tree::printPostOrder() { //O(N)
    std::string Total;

    Node* current = root;

    if(current->left!=nullptr) { //Bottom first.
        Total+=PrintPostOrderHelp(current->left)+",";
    }

    if(current->right!=nullptr) {
        Total+=PrintPostOrderHelp(current->right)+",";
    }

    Total+=current->Value->Name+",";

    return commaSpam(Total);
};


std::string tree::printLevelCount() { //O(1)
    int Top=HeightGetter(root); //Gives highest point. Therefore, all levels in it, long as balanced, which it is. Shrimple

    return std::to_string(Top);
};


Node* find(Node* n, int &Count) { //O(N)
    //Not here.
    if (Count<0) {
        return nullptr;
    }
    if(n==nullptr) {
        return nullptr;
    }




    Node* thing;

    /*if(n->left!=nullptr) {//Real, so count it.
        if(Count == 0) {
            return n->left;
        }
        Count -= 1;
    }

    if(n->right!=nullptr) {
        if(Count == 0) {
            return n->right;
        }
        Count -= 1;

    }*/
    thing = find(n->left, Count);
    if(thing!=nullptr) {
        return thing;
    }

    if(Count==0) {
        return n;
    }
    Count-=1;

    thing = find(n->right, Count);
    if(thing!=nullptr) {
        return thing;
    }
    return nullptr;
}
//Get the thing we are removing, then use the remove func to do the deed
std::string tree::removeInOrder(int N) { //O(N)
    Node* Target = find(root, N); // O(N)
    //find is broken.
    if(Target==nullptr) {
        return "unsuccessful";
    }
    remove(Target->Value->ID);
    return "successful";
};


Node* tree::rotateLeft (Node* node) // O(1)
{
    Node* newParent = node->right;
    Node* grandchild = node->right->left; //cutting off???
    newParent->left = node; //Shifty Shift. Essentially, move node->right to the top, make node it's child, and attach grandchild to the node.
    node->right = grandchild;

    if(grandchild!=nullptr) { //Parent shenanigans to make balance in insert work.
        grandchild->Parent = node;
    }
        newParent->Parent = node->Parent; //Corresponds to shifts above.
        node->Parent = newParent;


    //Recalculate height for affected nodes
    int NodeLeft = HeightGetter(node->left);

    int NodeRight = HeightGetter(node->right);

    node->BHeight=std::max(NodeLeft,NodeRight)+1;

    NodeLeft = HeightGetter(newParent->left);

    NodeRight = HeightGetter(newParent->right);

    newParent->BHeight=std::max(NodeLeft,NodeRight)+1;
    return newParent;
}
Node* tree::rotateRight (Node* node) // O(1)
{
    //Same but opposite of above.
    Node* newParent = node->left;
    Node* grandchild = node->left->right;

    newParent->right = node;

    node->left = grandchild;

    if(grandchild!=nullptr) {
        grandchild->Parent = node;
    }
    newParent->Parent = node->Parent;
    node->Parent = newParent;


    int NodeLeft = HeightGetter(node->left);

    int NodeRight = HeightGetter(node->right);

    node->BHeight=std::max(NodeLeft,NodeRight)+1;

    NodeLeft = HeightGetter(newParent->left);

    NodeRight = HeightGetter(newParent->right);

    newParent->BHeight=std::max(NodeLeft,NodeRight)+1;

    return newParent;


}
