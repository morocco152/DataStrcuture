#include<iostream>
using namespace std;
template<class T>class Node{
public:
	T data;
	Node<T> *next;
};
template<class T>class pila{
private:
	Node<T> * root;
public:
	pila(){root = NULL;}
	void push(T data){
		Node<T> * new_node = new Node<T>;
		new_node->data = data;
		new_node->next = root;
		root = new_node;
	}
	void show(){
		Node<T> * temp = root;
		while(temp!=NULL){
			cout << temp->data << "  ";
			temp = temp->next;
		}
		cout << endl;
	}
	void pop(){
		Node<T> * temp = root;
		root = temp->next;
		delete(temp);
	}
	void top(){
		cout<<root->data<<"\n";
	}
};