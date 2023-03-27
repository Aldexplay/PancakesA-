#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

// Función que devuelve la heurística de un estado dado (número de pancakes desordenados)
int heuristic(string state) {
    int count = 0;
    for (int i = 0; i < state.length() - 1; i++) {
        if (state[i] > state[i + 1]) {
            count++;
        }
    }
    return count;
}

// Función que devuelve todos los vecinos posibles de un estado dado
vector<string> get_neighbors(string state) {
    vector<string> neighbors;
    for (int i = 2; i <= state.length(); i++) {
        reverse(state.begin(), state.begin() + i);
        neighbors.push_back(state);
        reverse(state.begin(), state.begin() + i);
    }
    return neighbors;
}

// Estructura de datos para almacenar un estado y su costo de movimiento
struct Node {
    string state;
    int g;
    int f;
    string moves;
    bool operator<(const Node &other) const {
        return f > other.f;
    }
};

// Función de búsqueda A*
void a_star(string start_state) {
    priority_queue<Node> pq;
    map<string, int> g_values;
    pq.push({start_state, 0, heuristic(start_state), ""});
    g_values[start_state] = 0;
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        if (current.state == "ABCDEFGHIJ") {
            cout << "Solución encontrada en " << current.g << " movimientos: " << current.moves << endl;
            cout << "Orden final: " << current.state << endl;
            return;
        }
        for (string neighbor : get_neighbors(current.state)) {
            int g = current.g + 1;
            if (g_values.find(neighbor) == g_values.end() || g < g_values[neighbor]) {
                g_values[neighbor] = g;
                int f = g + heuristic(neighbor);
                string moves = current.moves + neighbor + " ";
                pq.push({neighbor, g, f, moves});
            }
        }
    }
}

int main() {
    srand(time(nullptr));
    string pancakes = "ABCDEFGHIJ";
    random_shuffle(pancakes.begin(), pancakes.end());
    cout << "Orden inicial: " << pancakes << endl;
    a_star(pancakes);
    return 0;
}

