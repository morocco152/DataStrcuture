//Nombre: Luis Angel Moroco Ramos --- CUI:20190743 --- CURSO:AED
#include <iostream>
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
    void insert(T data){
        isrtrec(root,data);
        balanceNode(root);
    }
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
        balanceNode(root);
    }
    void remove(T data, const int rem){rmvrc(root,data,rem);}
    //heigh function
    int high(Node<T>* node) const {return node == nullptr? -1 : node -> getht();}
    //balancing function
    Node<T>* balanceNode(Node<T>*& node){
        if(balanceFactor(node) > 1) {
            if(balanceFactor(node->left) > 0) 
                node = rotateLL(node);
            else 
                node = rotateLR(node);  
        }
        else if(balanceFactor(node) < -1) {
            if(balanceFactor(node->right) > 0)
                node = rotateRL(node);
            else
                node = rotateRR(node);
        }
        return node;
    }
    Node<T>* rotateLL(Node<T>* node){
        Node<T>* tempNode = node->left;
        node->left = tempNode->right;
        tempNode->right = node;
        return tempNode;
    }
    Node<T>* rotateLR(Node<T>* node){
        Node<T> *tempNode = node->left;
        node->left = rotateRR(tempNode);
        return rotateLL(node);
    }
    Node<T>* rotateRL(Node<T>* node){
        Node<T>* tempNode = node->right;
        node->right = rotateLL(tempNode);
        return rotateRR(node);
    }
    Node<T>* rotateRR(Node<T>* node){
        Node<T>* tempNode = node->right;
        node->right = tempNode->left;
        tempNode->left = node;
        return tempNode;
    }
    int balanceFactor(Node<T>*& node) const{
        int leftHeight  = node -> left  ? high(node->left)  : 0;
        int rightHeight = node -> right ? high(node->right) : 0;
        return (leftHeight - rightHeight);
    }
    //end balancing 
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
        int sh;
        std::vector<T> a;
        std::cout << "(1)Preorden - (2)inOrden - (3)postOrden :" ;std::cin >> sh;
        switch(sh){
            case 1: preOrden(a,root);break;
            case 2: inOrden(a,root);break;
            case 3: postOrden(a,root);break;
        }std::cout << std::endl;
    }
};
int main(){
    BST<int> abb;
    int ax,data,rem;
    do{
        std::cout << "(1)push - (2)find - (3)remove - (4)show -(5)exit :"; std::cin >> ax;
        switch(ax){
            case 1: std::cout << "data to insert: ";std::cin >> data;abb.insert(data);break;
            case 2: std::cout << "data to find: ";std::cin >> data;abb.find(data);break;
            case 3: std::cout << "data to remove: ";std::cin >> data;
                    std::cout << "(1)sucesor (2)predecesor:";std::cin>>rem;
                    abb.remove(data,rem);break;
            case 4: std::cout << "Showing: ";abb.show();break;
        }  
    }while(ax!=5);
    return 0;
}