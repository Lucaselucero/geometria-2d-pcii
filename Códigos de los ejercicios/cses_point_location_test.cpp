#include <iostream>

using namespace std;

typedef long long ll;

struct Vec {
    // Coordenadas (x, y)
    ll x, y; 

    // Constructor
    Vec(ll x = 0, ll y = 0) : x(x), y(y) {} 

    // Resta
    Vec operator-(Vec q) {return Vec(x - q.x, y - q.y);}

    // Producto cruz entre dos vectores
    ll operator^(Vec q) {return x * q.y - y * q.x;}
};

// Esta función determina la orientación entre tres puntos p1, p2 y p3
string orientacion(Vec p1, Vec p2, Vec p3) {
    Vec v1 = p2 - p1;  // Vector p1p2
    Vec v2 = p3 - p1;  // Vector p1p3

    ll producto_cruz = v1 ^ v2; // Usamos el operador ^ para el producto cruz

    if(producto_cruz < 0) {
        return "RIGHT";
    }
    else if(producto_cruz > 0) {
        return "LEFT";
    } 
    else {
        return "TOUCH";
    }
}

void test_case() {
    ll x1, y1, x2, y2, x3, y3;

    // Leemos las coordenadas de los puntos
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    // Creamos los puntos
    Vec p1(x1, y1);
    Vec p2(x2, y2);
    Vec p3(x3, y3);

    // Determina la orientación/posición de p3 respecto de la recta que pasa por p1 y p2
    cout << orientacion(p1, p2, p3) << endl;
}

int main() {
    int T; // Cant casos de prueba

    cin >> T;
    while(T--) {
        test_case();
    }
    return 0;
}