#include <iostream>
#include <vector>
 
using namespace std;

typedef long long ll;

struct Vec{
	// Coordenadas (x, y)
	ll x, y; 

    // Constructor
	Vec(ll x = 0, ll y = 0) : x(x), y(y) {}

	// Resta de dos vectores
	Vec operator-(Vec q) {return Vec(x - q.x, y - q.y);}

    // Producto escalar entre dos vectores
    ll operator*(Vec v) {return x * v.x + y * v.y;}

    // Comparación de igualdad con puntos/vectores
    bool operator==(Vec q) {return x == q.x && y == q.y;}  

    // Producto cruz entre dos vectores
    ll operator^(Vec q) {return x * q.y - y * q.x;}
};

// Determina de qué lado de la recta formada por a y b, se encuentra c
int side(Vec a, Vec b, Vec c) {
        // Obtenemos los vectores representativos de los segmentos (a, b) y (a, c)
        Vec v = b - a, w = c - a;
        ll res = v ^ w;
        if (res == 0) return 0; // c está en la línea que pasa por a y b
        if (res > 0) return 1;  // c está a la izquierda de la línea
        return -1;              // c está a la derecha de la línea
    }

// Verifica si los segmentos (p1, p2) y (p3, p4) se intersecan
bool se_intersecan(Vec p1, Vec p2, Vec p3, Vec p4) {
    // Determinamos la posición relativa de p3 con respecto a (p1, p2) y así sucesivamente
    int s1 = side(p1, p2, p3);
    int s2 = side(p1, p2, p4);
    int s3 = side(p3, p4, p1);
    int s4 = side(p3, p4, p2);

    // Para que dos segmentos se intersequen, un extremo de un segmento debe estar de un lado de 
    // la línea formada por el otro segmento y el otro extremo del otro lado. Esta lógica debe
    // ser válida para ambos segmentos.

    // Es muy improbable que la dirección del rayo coincida con uno de los lados del polígono debido
    // a la dirección que elegimos para el mismo, pero incluso en un caso muy raro en
    // donde eso sucediera, esta función ignora esas intersecciones, ya que en caso de
    // colinealidad, "s1 * s2 < 0 && s3 * s4 < 0" no va a ser < 0, y por lo tanto no lo
    // va a contar como intersección, lo cual es el comportamiento deseado

    // No queremos contar esto como intersección, ya que podríamos terminar contando
    // intersecciones adicionales que no corresponden a un cruce real. Más puntualmente,
    // cada vértice de ese lado podría contarse potencialmente como una intersección, dando
    // un resultado incorrecto
    return s1 * s2 < 0 && s3 * s4 < 0;
}

bool enSegmento(Vec a, Vec b, Vec c) {
     // Si el punto es uno de los extremos del segmento
    if (a == c || b == c) return true;
    
    // Para que c esté en el segmento (a, b), sus coordenadas x e y deben estar en el rango 
    // definido por las coordenadas 'x' e 'y' de a y b.
    bool xInRange = min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x);
    bool yInRange = min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
    return xInRange && yInRange;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    
    vector<Vec> poligono(n);
    for(int i = 0; i < n; i++) cin >> poligono[i].x >> poligono[i].y;
    
    for(int i = 0; i < m; i++) {
        Vec p;
        cin >> p.x >> p.y;
    
        bool boundary = false;
        // Verificamos si el punto p está en el borde del polígono
        for(int j = 0; j < n; j++){
            if(enSegmento(poligono[j], poligono[(j + 1) % n], p) &&
               side(poligono[j], poligono[(j + 1) % n], p) == 0){
                boundary = true;
                break;
            }
        }
    
        if(boundary){
            cout << "BOUNDARY" << endl;
            continue;
        }
    
        // Creamos un rayo desde el punto p hacia un punto arbitrariamente lejano
        Vec ray(1e9 + 7, 1e9 + 9);
        int count = 0;
        // Contamos cuántas veces el rayo interseca con los lados del polígono
        for(int j = 0; j < n; j++){
            if(se_intersecan(poligono[j], poligono[(j + 1) % n], p, ray)) count++;
        }
    
        if(count % 2 == 1){
            cout << "INSIDE" << endl;;
        } 
        else {
            cout << "OUTSIDE" << endl;
        }
    }
    return 0;
}