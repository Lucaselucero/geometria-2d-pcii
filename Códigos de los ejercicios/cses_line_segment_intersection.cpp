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

bool enSegmento(Vec a, Vec b, Vec c) {
     // Si el punto es uno de los extremos del segmento
    if (a == c || b == c) return true;
    
    // Para que c esté en el segmento (a, b), sus coordenadas x e y deben estar en el rango 
    // definido por las coordenadas 'x' e 'y' de a y b.
    bool xInRange = min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x);
    bool yInRange = min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
    return xInRange && yInRange;
}

// Verifica si los segmentos (p1, p2) y (p3, p4) se intersecan
bool se_intersecan(Vec p1, Vec p2, Vec p3, Vec p4) {
    // Comprobamos si algún punto de un segmento coincide con algún punto del otro segmento. 
    // Si dos puntos coinciden, entonces los segmentos se intersecan en ese punto
    if (p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4) return true;
    
    // Determinamos la posición relativa de p3 con respecto a (p1, p2) y así sucesivamente
    int s1 = side(p1, p2, p3);
    int s2 = side(p1, p2, p4);
    int s3 = side(p3, p4, p1);
    int s4 = side(p3, p4, p2);

    // Verificamos si los puntos son colineales. 
    // Si lo son, tenemos que chequear si alguno de los puntos del 
    // primer segmento está dentro del segundo segmento o viceversa.
	if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
        return enSegmento(p1, p2, p3) || enSegmento(p1, p2, p4) || enSegmento(p3, p4, p1) ||
               enSegmento(p3, p4, p2);
    }  

    // Para que dos segmentos se intersequen, un extremo de un segmento debe estar de un lado de 
    // la línea formada por el otro segmento y el otro extremo del otro lado. Esto tiene que 
    // valer para ambos segmentos.

    // El uso de <= en lugar de < garantiza que también consideramos el caso en que un punto 
    // está exactamente en la línea formada por el otro segmento (s1 o s2 o s3 o s4 es 0). 
    // Esto es consistente con la definición del problema que dice que si los segmentos 
    // comparten al menos un punto, se considera que se intersecan
    return s1 * s2 <= 0 && s3 * s4 <= 0;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Vec p1, p2, p3, p4;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
        if(se_intersecan(p1, p2, p3, p4)){
            cout << "YES" << endl;
        } 
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}