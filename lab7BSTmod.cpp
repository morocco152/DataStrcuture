//Nombre: Luis Angel Moroco Ramos --- CUI:20190743 --- CURSO:AED
#include <iostream>
#include <fstream>
#include <vector>
template <class T>
class Node{
private:
    T data;
    unsigned int ht;
public:
    Node *left,*right;
    Node(const T tmp, Node<T>* lf, Node<T>* rt , unsigned int h = 0) 
        : data {tmp}, left{lf}, right{rt}, ht{h} {}
    void setdata(const T data) {this -> data = data;}
    void setht(int ht) {this -> ht = ht;}
    T getdata() const {return data;}
    int getht() const {return ht;} 
};
    
template <class T>
class BST{
private:
    Node<T> *root;
public:
    //building
    BST(){root = nullptr;}
    //inserting function
    bool isrtrec(Node <T>*& node, const T data){
        if(!node){ 
            std::cout << "inserting:" << data << std::endl;
            node = new Node<T>(data,nullptr,nullptr);
        }
        else if (data == node -> getdata()){ 
            std::cout << "Value already exist!:" << data << std::endl;
            return false;
        }
        else if (data < node -> getdata())
            isrtrec(node -> left, data);
        else if (data > node -> getdata())
            isrtrec(node -> right, data);
        return true;
    }
    void insert(T data){isrtrec(root,data);}
    //find function
    Node<T>* findrecu(Node <T>* node, const T data){ 
        if(!node) return nullptr;
        if(data == node -> getdata()) return node;
        if(data < node -> getdata()) return findrecu(node -> left,data);
        if(data > node -> getdata()) return findrecu(node -> right,data);
        return nullptr;
    }
    void find(const T data){
        if(!findrecu(root,data))
            std::cout << data << ":not found" << std::endl;
        else
            std::cout << data << ":found" << std::endl; 
    }
    //remove function
    void rmvrc(Node<T>*& node,const T data,const int ax) { 
        if (!node)
            return;
        else if (data < node -> getdata())
            rmvrc(node->left, data, ax);
        else if (data > node -> getdata())
            rmvrc(node -> right, data, ax);
        else if (node -> left && node -> right) {
            if(ax == 1){ 
                node -> setdata(sucesorRecursivo(node -> right) -> getdata());
                rmvrc(node -> right, node -> getdata(), ax);
            }else if(ax == 2){ 
                node -> setdata(predecesorRecursivo(node -> left) -> getdata());
                rmvrc(node -> left, node -> getdata(), ax);
            }
        }
        else {
            Node<T>* nodeDeleter = node;
            node = (node->left) ? node->left : node->right;
            delete nodeDeleter;
        }
    }
    void remove(T data, const int rem){rmvrc(root,data,rem);}
    //heigh function
    int high(Node<T>* node) const {return node == nullptr? -1 : node -> getht();}

    Node<T>* sucesorRecursivo(Node<T>* node) const {
        if (!node)
            return nullptr;
        if (!(node->left))
            return node;
        return sucesorRecursivo(node->left);
    }
    Node<T>* predecesorRecursivo(Node<T>* node) const {
        if (!node)
            return nullptr;
        if (!(node->right))
            return node;
        return sucesorRecursivo(node->right);
    }
    //display function with types on vectors
    std::vector<T> preOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){ //root, left, right 
            a.push_back(tmp -> getdata());
            std::cout << tmp -> getdata() << " ";
            preOrden(a,tmp -> left);
            preOrden(a,tmp -> right);
        }
        return a;
    }
    std::vector<T> inOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){ //left , root , right 
            inOrden(a,tmp -> left);
            a.push_back(tmp -> getdata());
            std::cout << tmp -> getdata() << " ";
            inOrden(a,tmp -> right);
        }
        return a;
    }
    std::vector<T> postOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){ //left, right, root
          postOrden(a,tmp -> left);
          postOrden(a,tmp -> right);
          a.push_back(tmp -> getdata());
          std::cout << tmp -> getdata() << " ";
        }
        return a;
    }
    void show(){
        std::cout << "inorden:";
        std::vector<T> a;
        inOrden(a,root);
        std::cout << std::endl;
        std::cout << "preorden:";
        std::vector<T> b;
        preOrden(b,root);
        std::cout << std::endl;
        std::cout << "postorden:";
        std::vector<T> c;
        postOrden(c,root);
        std::cout << std::endl;
    }
};

template <class T>
void menu(BST<T> *a){
        int rem,ax;
        T data;
        do{
            std::cout << "(1)push - (2)find - (3)remove - (4)show -(5)exit :"; std::cin >> ax;
            switch(ax){
                case 1: std::cout << "data to insert: ";std::cin >> data;a->insert(data);break;
                case 2: std::cout << "data to find: ";std::cin >> data;a ->find(data);break;
                case 3: std::cout << "data to remove: ";std::cin >> data;
                        std::cout << "(1)sucesor (2)predecesor:";std::cin>>rem;
                        a->remove(data,rem);break;
                case 4: std::cout << "Showing: " << std::endl;a->show();break;
            }  
        }while(ax!=5);
        exit(1);
}

int main(){
    std::ifstream filereader("archivo.txt");
    if(filereader.is_open()){
        std::string label;
        filereader >> label;
        if(label == "int"){
            BST<int> a;
            int data;
            while(filereader >> data){a.insert(data);}
            a.show();
            menu(&a);
        }else if(label == "char"){
            BST<char> b;
            char data;
            while(filereader >> data){b.insert(data);}
            b.show();
            menu(&b);
        }else if(label == "string"){
            BST<std::string> c;
            std::string data;
            while(filereader >> data){c.insert(data);}
            c.show();
            menu(&c);
        }
    }
    filereader.close();
    return 0;
}