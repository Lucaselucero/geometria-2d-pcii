#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

struct Recta {
    ll a, b, c;
};

// Evalúa un punto en una Recta
ll evaluar(Recta r, ll x, ll y) {
    return r.a * x + r.b * y + r.c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ll n;
    cin >> n;

    vector<Recta> rectas(n);
    for (int i = 0; i < n; ++i) {
        cin >> rectas[i].a >> rectas[i].b >> rectas[i].c;
    }

    int count = 0;
    for (Recta r : rectas) {
        ll eval1 = evaluar(r, x1, y1);
        ll eval2 = evaluar(r, x2, y2);
        
        // Si los puntos se encuentran en distintos semiplanos, incremento count.
        if ((eval1 > 0 && eval2 < 0) || (eval1 < 0 && eval2 > 0)) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}