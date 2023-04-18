#include <iostream>
#include <fstream>
#include <windows.h>

#define N 8
#define K 100000

int read_matrix(int matrix[N][N]) {
    std::ifstream in(R"(C:\Users\annie\CLionProjects\lab_2\m1.txt)");
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

int sum_edges_vertices(int con_matrix[N][N]) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += con_matrix[i][j];
        }
    }
    return sum;
}

int euler(int matrix[N][N], int con_matrix_[N][N]) {
    int con_matrix[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            con_matrix[i][j] = con_matrix_[i][j];
        }
    }

    int p[K + 1];
    int p1;
    int p2;
    int s = 0;
    int k = sum_edges_vertices(con_matrix) / 2;
    int weight = 0;

    p1 = 0;
    p2 = k + 1;
    p[p1] = s;

    while (p1 >= 0) {
        int i, v = p[p1];
        for (i = 0; i < N; ) {
            if (con_matrix[v][i] != 0) {
                con_matrix[v][i] = con_matrix[v][i] - 1;
                con_matrix[i][v] = con_matrix[i][v] - 1;
                p[++p1] = i;
                v = i;
                i = 0;
            }
            else {
                i++;
            }
        }
        if (i >= N) {
            p[--p2] = p[p1--];
        }
    }

    if (p2 > 0) {
        std::cout << "Graph is not Eulerian" << std::endl;
    }
    else {
        std::cout << "Edge  : Weight \n";
        for (int i = 0; i < k; i++) {
            std::cout << p[i] + 1 << " - " << p[i + 1] + 1 << " : " << matrix[p[i]][p[i + 1]] << std::endl;
            weight += matrix[p[i]][p[i + 1]];
        }
    }
    return 0;
}

int add_edges(int con_matrix[N][N], int vert_degree[N], int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        if (vert_degree[i] % 2 != 0) {
            for (int j = 0; j < N; j++) {
                if (vert_degree[j] % 2 != 0 && con_matrix[i][j] != 0) {
                    con_matrix[i][j] = con_matrix[i][j] + 1;
                }
            }
        }
    }

    std::cout << "\nModified connectivity matrix: " << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << con_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    euler(matrix, con_matrix);

    return 0;
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

int if_euler(int con_matrix[N][N], int vert_degree[N], int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        if (vert_degree[i] != 0) {
            add_edges(con_matrix, vert_degree, matrix);
            break;
        }
        else {
            euler(matrix, con_matrix);
        }
    }
    return 0;
}

int vertex_degree(int con_matrix[N][N], int vert_degree[N], int matrix[N][N]) {
    std::cout << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vert_degree[i] += con_matrix[i][j];
        }
        if (vert_degree[i] % 2 != 0)
        {
            std::cout << "Vertex " << i + 1 << " is odd\n";
        }
    }
    if_euler(con_matrix, vert_degree, matrix);

    return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int matrix[N][N];
    int con_matrix[N][N];
    int vert_degree[N];

    std::cout << "Initial matrix: " << std::endl;
    read_matrix(matrix);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] != 0) {
                con_matrix[i][j] = 1;
            }
        }
    }
    connectivity_matrix(con_matrix, matrix);
    vertex_degree(con_matrix, vert_degree, matrix);

    system("Pause");
    return 0;
}
