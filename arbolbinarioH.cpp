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
        : data {tmp}, left{lf}, ht{h} {}
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
    int altura;
    BST(){root = nullptr;}

    bool isrtrec(Node <T>*& node, T data) {
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
        balanceNode(node);
    }
    void insert(T data){isrtrec(root,data);}

    Node<T>* findrecu(Node <T>* node, T data){ 
        if(!node) return nullptr;
        if(data == node -> getdata()) return node;
        if(data < node -> getdata()) return findrecu(node -> left,data);
        if(data > node -> getdata()) return findrecu(node -> right,data);
        return nullptr;
    }
    void find(T data){
        if(!findrecu(root,data))
            std::cout << data << ":not found" << std::endl;
        else
            std::cout << data << ":found" << std::endl; 
    }

    void rmvrc(Node<T>*& node,const T data) { 
        if (!node)
            return;
        else if (data < node -> getdata())
            rmvrc(node->left, data);
        else if (data > node -> getdata())
            rmvrc(node -> right, data);
        else if (node -> left && node -> right) {
            node -> setdata(SuceoPre(node) -> getdata());
            rmvrc(node -> right, node -> getdata());
        }
        else {
            Node<T>* nodeDeleter = node;
            node = (node->left) ? node->left : node->right;
            delete nodeDeleter;
        }
    }
    void rmv(T data){rmvrc(root,data);}

    int high(Node<T>* node) const {return node == nullptr? -1 : node -> getht();}

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
        int leftHeight  = node->left  ? high(node->left)  : 0;
        int rightHeight = node->right ? high(node->right) : 0;
        return (leftHeight - rightHeight);
    }

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

    Node<T>* SuceoPre(Node<T>* node){
        int ax;
        std::cout << "(1)Predecesor (2)Sucesor :" ; std::cin >> ax;
        switch(ax){
            case 1:return sucesorRecursivo(node -> right);break;
            case 2:return predecesorRecursivo(node -> left);break;
        }exit(1);
    }

    std::vector<T> preOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){
            a.push_back(tmp -> getdata());
            std::cout << tmp -> getdata() << " ";
            preOrden(a,tmp -> left);
            preOrden(a,tmp -> right);
        }
        return a;
    }

    std::vector<T> inOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){
            inOrden(a,tmp -> left);
            a.push_back(tmp -> getdata());
            std::cout << tmp -> getdata() << " ";
            inOrden(a,tmp -> right);
        }
        return a;
    }

    std::vector<T> postOrden(std::vector<T>& a, Node<T> *tmp) const {
        if(tmp != NULL){
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