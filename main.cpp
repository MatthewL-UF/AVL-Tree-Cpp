#include <iostream>
#include <sstream>
#include <vector>
#include "tree.h"

using namespace std;

vector<string>splitter3(string &s, char delim) {
	vector<string> temp;
	string tempWord;
	bool toggle = false;
	for (char c : s) {
		if (c=='\"') {
			toggle = !toggle;
		}
		else if(!toggle && c==delim) {
			temp.push_back(tempWord);
			tempWord="";
		} else {
			tempWord+=c;
		}
	}
	temp.push_back(tempWord);
	return temp;
};

int main(){
	tree *Treebeard = new tree();

	int num;
	cin >> num;
	cin.ignore();

	for(int i = num; i > 0; i--) {
		string temp;
		getline(cin, temp);
		vector<string> NewStr = splitter3(temp, ' ');

		if(NewStr[0]=="insert"){
			    //ITS STILL YOU. Now the issue is how to deal with 00000004 vs 4
				if(NewStr[2].length()==8) {
					cout<<Treebeard->insert(NewStr[1],stoi(NewStr[2]))<<endl;
				} else {
					cout<<"unsuccessful"<<endl;
				}

				//.substr(1, NewStr[1].length() - 2)
		}
		else if(NewStr[0]=="remove"){
				cout<<Treebeard->remove(stoi(NewStr[1]))<<endl;;

			}
		else if(NewStr[0]=="search"){
				if(NewStr[1][0]>='0' && NewStr[1][0]<='9') { //ID entered.
					//int temp = stoi(NewStr[1]);
					cout<<Treebeard->search(stoi(NewStr[1]))<<endl;
				} else {
					cout<<Treebeard->search(NewStr[1])<<endl; //Name Entered
				}


			}
		else if(NewStr[0]=="printInorder"){
				cout<<Treebeard->printInOrder()<<endl;;

			}
		else if(NewStr[0]=="printPreorder"){
				cout<<Treebeard->printPreOrder()<<endl;; //Preorder and Post order printing wrong. Tree intact

			}
		else if(NewStr[0]=="printPostorder"){
				cout<<Treebeard->printPostOrder()<<endl;;

			}
		else if(NewStr[0]=="printLevelCount"){
				cout<<Treebeard->printLevelCount()<<endl;;

			}
		else if(NewStr[0]=="removeInorder"){
				cout<<Treebeard->removeInOrder(stoi(NewStr[1]))<<endl; //Issue

			}
		else{
				std::cout<<"Invalid Input"<<endl;
			}
		}

	return 0;
}
