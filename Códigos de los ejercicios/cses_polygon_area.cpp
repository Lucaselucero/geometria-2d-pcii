#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Vec {
    // Coordenadas (x, y)
    ll x, y;

    Vec operator-(Vec q) { return {x - q.x, y - q.y}; }  // Resta de vectores
    ll operator^(Vec q) { return x * q.y - y * q.x; }    // Producto cruz entre dos vectores
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Vec> vertices(n);
  
    // Leemos los vértices/puntos del polígono
    for (int i = 0; i < n; i++) {
        cin >> vertices[i].x >> vertices[i].y;
    }

    // Calculamos el área utilizando triangulaciones desde el vértice 0
    ll area = 0;
    for (int i = 1; i < n - 1; i++) {
        // El triángulo formado por los vértices 0, i e i + 1 del polígono
        Vec v1 = vertices[i] - vertices[0];
        Vec v2 = vertices[i + 1] - vertices[0];

        // Calculamos el área del triángulo haciendo el producto cruz entre v1 y v2
        // y acumulamos el resultado en 'area'. De esta manera, en 'area' se van 
        // sumando las áreas de todos los triángulos, y al finalizar, tendremos el
        // el área del polígono
        area += v1 ^ v2;
    }

    // Tomamos el valor absoluto para obtener el área
    // ¿Por qué? Porque el producto cruz puede dar negativo dependiendo de la orientación
    
    // Observar que el problema pide '2a' donde 'a' es el área
    // del polígono, por lo que no tenemos que dividir por 2 en este caso
    cout << abs(area) << endl;

    return 0;
}
