#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cmath>

using namespace std;

string toBinary(int n)           //Funcion que usamos para convertir de decimal a binario
{
    string r;
    while (n != 0) {
        r += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    return r;
}

int toDecimal(string n) {         //Funcion que usamos para convertir de binario a decimal
    int r = 0;
    char a[2];
    for (int i = 0, k = 0; i < n.length(); i++, k++) {
        a[0] = n[i];
        r += atoi(a) * pow(2, k);
        //cout << atoi(a) << '\n';
    }
    return r;
}

string proyection(string a, string b) {      //En este funcion hacemos la convinacion de los binarios dados, para el Z- order
    int a_l = a.length();
    int b_l = b.length();
    int max;
    string r;
    if (a_l < b_l) {
        max = b_l;
        for (int i = 0; i < (b_l - a_l); i++) {
            a.push_back('0');
        }
    }
    else {
        max = a_l;
        for (int i = 0; i < (a_l - b_l); i++) {
            b.push_back('0');
        }
    }
    for (int i = 0; i < max; i++) {
        r.push_back(b[i]);
        r.push_back(a[i]);
    }
    //cout << r << endl;
    return r;
}

int main (){
    srand(time(NULL));

    int cant_elem = 5000;
    int dim = 10;
    int** set = new int* [cant_elem];

    for (int i = 0; i < cant_elem; i++) {
        set[i] = new int[dim];
        for (int j = 0; j < dim; j++) {
            set[i][j] = (rand() % 10) + 1;  //DE 1 a 11, para poder ver cuando no se agrega nada en ese espacio de memoria
        }
    }

    int proyeccion[50000];
    for (int i = 0; i < 50000; i++) {        //Aqui rellenamos de 0's para poder ver cuales si fueron insertados y cuales no.
        proyeccion[i] = 0;
    }

    /*string proof = toBinary(2);
    cout << "Binary -> " << proof << '\n';
    cout << "Decimal -> " << toDecimal(proof) << '\n';*/
    int ubi;                                                  //Aqui hacemos la proyeccion, el unico problema que ubo fue que para poder almacernarlo 
    for (int i = 0; i < cant_elem; i++) {                     //en un array, tendriamos que tener un array de 37 millones
        for (int j = 0; j < dim; j++) {                       //lo que requiere de mucha memoria
            ubi = toDecimal(proyection(toBinary(i), toBinary(j)));
            if (ubi <= 50000) {
                proyeccion[ubi] = set[i][j];
            }
        }
    }
    cout << "Proyeccion -> " << proyeccion[0] << ' ' << proyeccion[1] << ' ' << proyeccion[2] << ' ' << proyeccion[3] << ' ' << proyeccion[4] << ' ' << proyeccion[5] << endl;
    cout << "Datos Originales ->" << set[0][0] << ' ' << set[0][1] << ' ' << set[1][0] << ' ' << set[1][1] << ' ' << set[0][2] << ' ' << set[0][3] << endl;

    //cout << toDecimal(proyection(toBinary(5000), toBinary(10))) << endl;
    cout << "Done!\n";

    for (int i = 0; i < cant_elem; i++) {   //Eliminamos nuestra memoria dinamica
        delete[] set[i];
    }
    delete[] set;
	return 0;
}