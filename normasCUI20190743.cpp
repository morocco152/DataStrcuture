#include <iostream>
#include <cmath>
double norm2(int a, int b){
    double result = 0;
    result = sqrt(pow(a,2) + pow(b,2));
    return result;
}
//hilbert 
void hilbert(int n){ 
    float H[n][n]; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {  
            H[i][j] = (float)1.0/((i + 1)+(j + 1) -1.0); 
        } 
    } 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++)  
            std::cout << H[i][j] << " ";         
        std::cout << std::endl; 
    } 
} 
//stop hilbert
//vandermore
void createVandermonde(int *iarr, int **vander, int n){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            vander[i][j] = pow(iarr[i], n - j - 1);
}

int **array2_create(int row, int col){
    int **arr=NULL;
    arr = (int **) malloc((row*sizeof(int*)));
    if (!arr) {
        fprintf(stderr, "matrixi_create : error allocation row");
        exit(0);
    }
    arr[0]=(int*) malloc((row*col)*sizeof(int));
    if (!arr[0]) {
        fprintf(stderr, "matrixi_create : error allocation column");
        exit(0);
    }
    for(int i=1; i<row; i++)
        arr[i]=arr[i-1] + col;
    return arr;
}

void array2_free(int **arr){
    free(arr[0]);
    free(arr);
}

void printArray2(int **arr, int n, int ny){
    for(int i = 0; i < ny; i++){
        for(int j = 0; j < n; j++)
            printf("%i \t", arr[i][j]);
        std::cout << std::endl;    
    }
    std::cout << std::endl;
}

void printArray1(int *arr, int n){
    for(int i = 0; i < n; i++)
        printf("%i \t", arr[i]);
    std::cout << std::endl;
    std::cout << std::endl;
}
//vnademore
int main(){
    int numeros[100][100],filas,columnas;
    std::cout << "#f:"; std::cin >> filas;
    std::cout << "#c:"; std::cin >> columnas;

    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){ 
            std::cout << "#" ; std::cin >> numeros[i][j]; 
        }
    }

    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            std::cout << numeros[i][j] <<  "   " ;
        std::cout << std::endl;
    }

    int c = 0; // usando la norma 0 
    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            if(numeros[i][j] != 0)
                c++;      
    }

    std::cout << "Norma 0:" << c << std::endl;

    int count = 0; // usando la norma 1
    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            count += abs(numeros[i][j]);
    }
    std::cout << "Norma 1:" << count << std::endl;

    std::cout << "Traspuesta:" << std::endl;
    int numeros1[100][100];
    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){  
            numeros1[i][j] = numeros[j][i]; 
        }
    }

    for (int i = 0 ; i < filas ; i++){
        for (int j = 0 ; j < columnas ; j++)
            std::cout << numeros1[i][j] <<  "   " ;
        std::cout << std::endl;
    }

    double max = 0;
    double nor = 0;
    for (int i = 0 ; i < filas ; i++){
        for(int j = 0 ; j < columnas ; j++){ 
            nor = norm2(numeros1[i][j],numeros[i][j]);
            if(nor >= max)
                max = nor;
        }
    }

    std::cout << "norm2:" << max << std::endl;
    //
    std::cout << "hilbert" << std::endl;
    int n;
    std::cout << "número de matriz:"; std::cin >> n; 
    hilbert(n); 
    //
    std::cout << "vandermore" << std::endl;
    int *iarr, **vandermonde;
    vandermonde = array2_create(n, n);
    iarr = (int*) calloc (n, sizeof(int));
    for(int i = 0; i < n; i++)
        iarr[i] = i + 1;
  
    createVandermonde(iarr, vandermonde, n);
    printArray1(iarr, n);
    printArray2(vandermonde, n, n); 
    free(iarr);
    array2_free(vandermonde);
 
    return 0;
}