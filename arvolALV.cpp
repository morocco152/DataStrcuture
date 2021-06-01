#include "iostream"
using namespace std;

template <class T>
class Node{
public:
	T data;
	Node *left;
	Node *right;
public:
	Node(T tmp){
		data = tmp;
		left = NULL;
		right = NULL;
	}
};

template <class T>
class BST{
private:
	Node<T> *root;
public:
	BST(){root = nullptr;}
	bool find(T data){
		Node<T> *tmp = root;
		while(tmp!=NULL){
			if (tmp -> data == data){
				cout << "found:" << data << endl;
				return true;
			}
			else
				tmp = (tmp -> data > data ? tmp -> left : tmp -> right);
		}
		cout << "Not found" << endl;
		return false;
	}
	bool insert(T data){
		if (root == NULL){
			Node<T> *new_node = new Node<T>(data);
			root = new_node;
			return true;
		}else{
			Node<T> *tmp = root;
			Node<T> *prev = NULL;
			while(tmp!=NULL){
				if (tmp -> data == data){
					cout << "found" << data << endl;
					return false;
				}
				else
					prev = tmp;
					tmp = tmp -> data > data ? tmp -> left : tmp -> right;
			}
			cout << "inserting node:" << data << endl;
			Node<T> *new_node = new Node<T>(data);
			if (data < prev -> data)
				prev -> left = new_node;
			else
				prev -> right = new_node;
			return true;
		}
	}
};

int main(){
	BST<int> abb;
	abb.insert(12);
	abb.insert(10);
	abb.insert(7);
	abb.insert(30);
	abb.find(30);	
	abb.find(56);
	return 0;
}