#include "testing.cpp" 
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