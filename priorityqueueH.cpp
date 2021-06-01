#include<iostream>
#include<fstream>
using namespace std;
template<class T>class Node{ 
public:
	T data;
	string label;
	Node<T> *next;
};
template<class T>class priority_queue{
private:
	Node<T> * root;
	Node<T> * final;
public:
	priority_queue(){
		root = NULL;
		final = NULL;
	}
	void enqueue(string label,T data){
		Node<T> * new_node = new Node<T>;
		new_node -> label = label;
		new_node -> data = data;
		new_node -> next = NULL;

		if(root == NULL){
			root = new_node;
			final = new_node;
		}else if (data > root -> data){
			Node<T> *temp = root;
			do{
				if(data > temp -> data)
					temp = temp -> next;
				break;
			}while(temp);
			final -> next = new_node;
			final = new_node;
		}else if (data < root -> data){
			new_node -> next = root;
			root = new_node;
		}
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
		enqueue(proceso.label,proceso.data);
	}
  	T front(){
    	T elemento = root -> data;
    	return elemento;
    }
};