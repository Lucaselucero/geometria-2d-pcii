#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;


struct Punto{
    ll x, y;
    Punto(ll x = 0, ll y = 0) : x(x), y(y) {}
};

ll sq_dist(Punto a, Punto b){
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}

struct Circulo{
    ll r;
    Punto centro;

    /*
    Calculamos la distancia cuadrada en vez de la distancia, porque la distancia
    puede ser un número real que no necesariamente es entero, y nos molesta comparar puntos flotantes
    */
    bool contiene_punto(Punto p){
        // En algunos problemas, este chequeo sería con “<=”, pero en este problema nos dicen que no hay puntos sobre la circunferencia
        return sq_dist(centro, p) < r * r;
    }
};

int main(){
    // Estas dos líneas hacen que cin/cout sea tan rápido como scanf/printf
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    /*
    n: cantidad de puntos
    m: cantidad de cercas
    k: cantidad de queries
    */
    while(cin >> n >> m >> k){
        vector<Punto> puntos(n);
        vector<Circulo> circulos(m);

        for(int i = 0; i < n; i++) cin >> puntos[i].x >> puntos[i].y;
        for(int i = 0; i < m; i++) cin >> circulos[i].r >> circulos[i].centro.x >> circulos[i].centro.y;

        // Precalculamos qué Puntos contiene cada Circulo
        vector<vector<bool>> puntosDentroDe(m, vector<bool>(n, false));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(circulos[j].contiene_punto(puntos[i])) {
                    puntosDentroDe[j][i] = true;
                }
            }
        }

        for(int i = 0; i < k; i++){
            int a, b;
            cin >> a >> b;
            a--; b--; // Para que quede indexado desde 0
            int count = 0;
            for(int j = 0; j < m; j++) {
               if(puntosDentroDe[j][a] != puntosDentroDe[j][b]) count++;
            }
            cout << count << endl;
        }
    }
    return 0;
}
