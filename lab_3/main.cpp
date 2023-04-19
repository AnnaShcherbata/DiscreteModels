#include <iostream>
#include <fstream>
#include <windows.h>

#define N 6

int read_matrix(int matrix[N][N]) {
    std::ifstream in(R"(C:\Users\annie\CLionProjects\lab_3\m1.txt)");
    if (in.is_open()) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                in >> matrix[i][j];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                std::cout << matrix[i][j] << "\t";
            std::cout << "\n";
        }

        in.close();
        return **matrix;
    }
    else {
        std::cout << "File not found.";
        return 0;
    }
}

int connectivity_matrix(int con_matrix[N][N], int matrix[N][N]) {
    std::cout << "\nConnectivity matrix: " << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > 0) {
                con_matrix[i][j] = 1;
            }
            else {
                con_matrix[i][j] = matrix[i][j];
            }
            std::cout << con_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return **con_matrix;
}

int hamilton(int k, int con_matrix[N][N], int c[N], int path[N], int v0) {
    int v, q1 = 0, k1;
    for (v = 0; v < N && !q1; v++) {
        if (con_matrix[v][path[k - 1]] || con_matrix[path[k - 1]][v]) {
            if (k == N && v == v0) {
                q1 = 1;
            }
            else if (c[v] == -1) {
                c[v] = k; path[k] = v;
                k1 = k + 1;
                q1 = hamilton(k1, con_matrix, c, path, v0);
                if (!q1) c[v] = -1;
            }
            else continue;
        }
    }   return q1;
}

int if_hamilton(int con_matrix[N][N], int c[N], int path[N], int v0) {
    std::cout << "\nHamiltonian cycle:\n";
    for (int j = 0; j < N; j++) {
        c[j] = -1;
    }
    path[0] = v0;
    c[v0] = v0;

    if (hamilton(1, con_matrix, c, path, v0)) {}
    else {
        std::cout << "There are no solutions.\n";
    }
    return *path;
}

int output(int matrix[N][N], int path[N]) {
    int weight = 0;
    std::cout << "Edge  : Weight \n";
    for (int i = 0; i < N; i++) {
        if (i == N - 1) {
            std::cout << path[i] + 1 << " - " << path[0] + 1 << " : " << matrix[path[i]][path[0]] << std::endl;
            weight += matrix[path[i]][path[0]];
        }
        else {
            std::cout << path[i] + 1 << " - " << path[i + 1] + 1 << " : " << matrix[path[i]][path[i + 1]] << std::endl;
            weight += matrix[path[i]][path[i + 1]];
        }
    }
    return  0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int matrix[N][N];
    int con_matrix[N][N];

    int c[N];
    int path[N];
    int v0 = 0;

    std::cout << "Initial matrix: " << std::endl;
    read_matrix(matrix);
    connectivity_matrix(con_matrix, matrix);

    if_hamilton(con_matrix, c, path, v0);
    output(matrix, path);

    system("Pause");
    return 0;
}