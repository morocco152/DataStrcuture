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
	void robin(int q){ // 4 -> 21 -> 40  == 65 
		int quantum = q;
		int current = 0;
		ofstream filewriter("procesos.txt");
		while (!empty()){
			Node<T> proceso = dequeue();
			    filewriter << "tiempo:" << current << " " << proceso.label << " " << "entra en proceso" << "\n";
			if (proceso.data <= quantum){
				current += proceso.data;
				filewriter << "tiempo:" << current << "  " << proceso.label << "  " << "termina" << "\n";
			}else{
				proceso.data -= quantum;
				current += quantum;
				filewriter << "tiempo:" << current << "  "<< proceso.label << "  " << "se conmuta" << "\n";
 				enqueue(proceso.label,proceso.data);
			}
		}
		filewriter.close();
	} 
};
int main(){	
	priority_queue<int> p;
	ifstream filereader("procesos.txt");
	if(filereader.is_open()){
		string label;
		int time,q;
		filereader >> q;
		while(filereader >> label >> time){
			p.enqueue(label,time);
		}p.robin(q);
	}filereader.close();
	return 0;
}