#include<iostream>
#include<string>
using namespace std;
struct Node{
	int data;
	Node *next;
};
class list{
private:
	Node * root;
public:
	list(){
		root = NULL;
	}
	void insert(int data){
		//crear nodo
		Node * new_node = new Node;
		//actualizar info
		new_node->data = data;
		new_node->next = NULL;
		//modificar punteros
		if(root == NULL){
			root = new_node;
		}
		else{
			Node * tmp = root;
			while(tmp->next!=NULL){
				tmp = tmp->next;
			}
			tmp->next=new_node;
		}
	}
	void print(){
		Node * tmp = root;
		while(tmp){
			cout << tmp->data << " -> ";
			tmp = tmp -> next;
		}
		cout << " NULL " << endl;
	}
};
int main(){
	list list_aed;
	list_aed.insert(5);
	list_aed.insert(4);
	list_aed.insert(9);
	list_aed.print();
}
