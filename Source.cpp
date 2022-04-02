#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;

int elements = 20000;

vector<vector<int>> generate(int dims) {
    vector<vector<int>> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < elements; i++) {
        vector<int> holder;
        for (int j = 0; j < dims; j++) {
            holder.push_back(dist(gen));
        }
        result.push_back(holder);
    }

    return result;
}

vector<int> distance(vector<vector<int>> a) {
    vector<int> result;
    for (int i = 1; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            int p = a[i][j];
            int q = a[0][j];
            int dist = pow(p - q, 2);
            result.push_back(dist);
        }
    }
    return result;
}

vector<int> cluster(vector<int> a) {
    vector<int> result;
    for (int i = 0; i < a.size(); i++) {
        int clust = 0;
        for (int j = 0; j < a.size(); j++) {
            if (a[i] == a[j]) {
                clust++;
            }
        }
        result.push_back(clust);
    }
    return result;
}

void writer(vector<int> a, vector<int> b) {
    ofstream temp;
    temp.open("distances.txt");
    for (int i = 0; i < a.size(); i++) {
        temp << a[i] << "\n";
    }
    temp.close();
    temp.open("clustering.txt");
    for (int i = 0; i < b.size(); i++) {
        temp << b[i] << "\n";
    }
    temp.close();
    return;
}

void display(vector<int> a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << endl;
    }
    return;
}
void specialDisplay(vector<vector<int>> a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Cantidad de datos por defecto: 20000" << endl;
    int dimensiones;
    cout << "Ingresar la cantidad de dimensiones: ";
    cin >> dimensiones;
    std::chrono::time_point<std::chrono::high_resolution_clock> starter, ender;
    starter = std::chrono::high_resolution_clock::now();
    cout << "Generando elementos..." << endl;
    vector<vector<int>> start = generate(dimensiones);
    cout << "Calculando distancias..." << endl;
    vector<int> proc = distance(start);
    cout << "Agrupando distancias..." << endl;
    vector<int> end = cluster(proc);
    cout << "Escribiendo informacion en archivos de texto..." << endl;
    writer(proc, end);
    cout << "Proceso terminado" << endl;
    ender = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(ender - starter).count();
    cout << "Duración del proceso: " << duration/(pow(10,9)) << " segundos" << endl;
}
