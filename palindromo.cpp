#include <iostream>
#include <string>
using namespace std;
struct Node{
	char data;
	Node *next;
	Node *ant;
};
class list{
private:
	Node * root;
	Node * fin;
public:
	list(){
		root = NULL;
		fin = NULL;
	}
	void insert(char data){
		Node * new_node = new Node;
		new_node->data = data;
		if( data == ' '){return;}
		if(root == NULL){
			root = new_node;
			fin = new_node;
			new_node -> next = NULL;
			new_node -> ant = NULL;
		}else{
			fin -> next = new_node;
			new_node -> ant = fin;
		}fin = new_node;
	}
	bool print(){
		bool a = true;
		Node * tmp = root;
		Node * tmp1 = fin;
		do{
			if( tmp -> data == tmp1 -> data ){
				tmp = tmp -> next;
				tmp1 = tmp1 -> ant;
			}else{return false;}
		}while((tmp->next and tmp1->ant));
		return true;
	}
};
int main(){
	list list_aed;
	string code;
	cout << "INGRESE LA FRASE O PALABRA: ";getline(cin,code);
	for (int i = 0; i < code.size(); ++i){
		code[i]=tolower(code[i]);
		list_aed.insert(code[i]);
	}
	if(list_aed.print()==true){cout << "si" << endl;}
	else{cout << " no " << endl;}
	return 0;
}
