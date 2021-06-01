#include<iostream>
#include<string>
using namespace std;
// LAB2->LUIS ANGEL MOROCO RAMOS
//Lo que hago aquí es crear una lista de libros con la STRUCT libro para sus caracteriaticas y su puntero a siguiente.
struct nodo{
    struct libro{
        string code,name,edit,autor,resu;
        int anio;
    }libro;
    int size=0;
    nodo *nex;
};
typedef nodo *ptrpila;
//paso los valores y los guardo en sus direcciones
void push(ptrpila &p,string valor,int _anio,string _title,string _editto,string _auttor,string _resumen){
    ptrpila aux=new(struct nodo);
    aux->libro.code=valor;
    aux->libro.anio=_anio;
    aux->libro.name=_title;
    aux->libro.edit=_editto;
    aux->libro.autor=_auttor;
    aux->libro.resu=_resumen;
    if(p==NULL){p=aux;}//comprobar en los casos de lista vacia y lista con más de un elemento
    else{
        ptrpila reco=p;
        while(reco->nex!=NULL){reco=reco->nex;}
        reco->nex=aux;
    }
    
    p->size+=1;cout<<"----------"<<aux->libro.name<<"-------->AGEGADO!!"<<endl;
}
void print(ptrpila &p){//funcion print para ahorrar mucho codigo, coge la direccion de memoria de del puntero a el elemento de la lista y extrae toda su informacion
    cout<<"******ISBN:"<<p->libro.code<<endl;
    cout<<"          ANIO:"<<p->libro.anio<<endl;
    cout<<"          TITULO:"<<p->libro.name<<endl;
    cout<<"          EDITORIAL:"<<p->libro.edit<<endl;
    cout<<"          AUTOR:"<<p->libro.autor<<endl;
    cout<<"          RESUMEN:"<<p->libro.resu<<endl;
}
void show(ptrpila &p){//comprobacion de lista vacia y si no imprimira los elementos de la lista con 'print' y correra al nex->
    if(p==NULL){cout<<"          !!!LIBRERIA VACIA!!!";return;}
    ptrpila aux=p;
    while(aux!=NULL){
        print(aux);
        aux=aux->nex;
    }
}
void pop(ptrpila &p,string valor){//como no tengo la posicion, sino solo el ISBN, buscar no serviria de nada pues no puedo retroceder entonces
    if(p==NULL){cout<<"          !!!LIBRERIA VACIA!!!";return;}
    if((p->size)==1){p->size-=1;p=NULL;return;}
    ptrpila aux=p;
    int pos=0;
    while((aux->libro.code).compare(valor)!=0){// cuento los saltos hasta llegar al elemento y la tomo como referencia
        aux=aux->nex;pos++;
    }
    if(pos<=(p->size)){
        ptrpila del;
        ptrpila reco=p;
        for (int i=1;i<pos-2;++i){reco=reco->nex;}//como ya  tengo la posicion, solo voy una pos antes y redirecciono punteros  (2)->  X3X -> 4   
        ptrpila prox=reco->nex;
        reco->nex=prox->nex;
        del=prox;
        
        delete del;
    }
    p->size-=1;cout<<"------------------>BORRADO!!"<<endl;
    
}
void search(ptrpila &p,string valor,int c){//hacemos la busqueda, pasamos la lista, el valor de busqueda y el tipo
    ptrpila aux=p;
    switch(c){
        case 1:
            while((aux->libro.code).compare(valor)!=0){aux=aux->nex;}
            print(aux);break;
        case 2:
            while((aux->libro.name).compare(valor)!=0){aux=aux->nex;}
            print(aux);break;
        case 3:
            int x=p->size;
            do{
                if((aux->libro.autor).compare(valor)==0){print(aux);}//por autor, pero puede que un autor halla escrito muchos libros asi que recorremos toda su lista sin parar hasta el final
                aux=aux->nex;
                x--;
            }while(x!=0);break;//solo cuando la lista llega a cero termina
    }
}

int main(){ //declaraciones
    int ax,anio;
    string data,title,editto,auttor,resumen;
    ptrpila p=NULL;//ptr inciial a null
    do{
        cout<<"***BIENVENIDO A LIBRERIA***\n   Agregar libro(1)\n   Eliminar libro(2)\n   Mostrar todo(3)\n   Buscar libro(4)\n   Salida(5)\n******ACCION: ";cin>>ax;
        switch(ax){
            case 1:
                cout<<"       ISBN:";cin>>data;
                cout<<"       Año:";cin>>anio;
                cout<<"       titulo:";cin>>title;
                cout<<"       Editorial:";cin>>editto;
                cout<<"       Autor:";cin>>auttor;
                cout<<"       Resumen:";cin>>resumen;
                push(p,data,anio,title,editto,auttor,resumen);break;
            case 2:
                cout<<"-------ISBN DEL LIBRO:";cin>>data;
                pop(p,data);break;
            case 3:
                cout<<"------------TODOS NUESTROS LIBROS------------"<<endl;
                show(p);
                cout<<"---------------------------------------------"<<endl;break;
            case 4://escogemos el metodo de busqueda que luego sera redireccionado en search void 
                cout<<"--------ELIGE UN METODO DE BUSQUEDA"<<endl;
                cout<<"           ISBN(1)\n           Titulo(2)\n           Autor(3)\n*************Opcion:";cin>>ax;
                switch(ax){
                    case 1:
                        cout<<"           ISBN: ";cin>>data;
                        search(p,data,1);break;
                    case 2:
                        cout<<"           Titulo: ";cin>>data;
                        search(p,data,2);break;
                    case 3:
                        cout<<"              Autor: ";cin>>data;
                        cout<<"------------LIBROS DE ESTE AUTOR------------"<<endl;
                        search(p,data,3);
                        cout<<"--------------------------------------------"<<endl;break;
                }cout<<"\n\n";
        }cout<<"\n\n";
    }while(ax!=5);
    return 0;
}