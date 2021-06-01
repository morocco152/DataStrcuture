#include<iostream>
using namespace std;
template<class T>class Node{ 
public:
	T data;
	Node<T> *next;
};
template<class T>class cola{
private:
	Node<T> * root;
	Node<T> * final;
public:
	cola(){
		root = NULL;
		final = NULL;
	}
	void enqueue(T data){
		Node<T> * new_node = new Node<T>;
		new_node -> data = data;
		new_node -> next = NULL;

		if(root==NULL){root = new_node;
		}else{final -> next = new_node;}
		final = new_node;
	}
	void show(){
		Node<T> * temp = root;
		while(temp!=NULL){
			cout << temp -> data << "  ";
			temp = temp -> next;
		}
    	cout << endl;
	}
	Node<T> dequeue(){
		if(root==NULL){cout << "NULL!" << endl;exit(1);}
		Node<T> *temp = root;
		if(root == final){
			root = NULL;
			final = NULL;
		}else{root = root -> next;}
		Node<T> elemento = *temp;
		delete(temp);
		return elemento;
	}
	bool empty(){
		if(root == NULL)
			return true; 
		return false;
	}
	void back(){
		Node<T> proceso = dequeue();
		enqueue(proceso.data);
	}
  	T front(){
        T elemento = root -> data;
    	return elemento;
  	}
};