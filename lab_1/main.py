import numpy as np
import sys

class Graph():
    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[0 for column in range(vertices)]
                      for row in range(vertices)]

    def print_res(self, parent):
        print("Edge \tWeight")
        for i in range(1, self.V):
            print(parent[i] + 1, "-", i + 1, "\t", self.graph[i][parent[i]])

    def minKey(self, key, mstSet):

        min = sys.maxsize

        for v in range(self.V):
            if key[v] < min and mstSet[v] == False:
                min = key[v]
                min_index = v

        return min_index

    def prim(self):

        key = [sys.maxsize] * self.V
        parent = [None] * self.V
        key[0] = 0
        mstSet = [False] * self.V

        parent[0] = -1

        for cout in range(self.V):

            u = self.minKey(key, mstSet)

            mstSet[u] = True

            for v in range(self.V):
                if self.graph[u][v] > 0 and mstSet[v] == False and key[v] > self.graph[u][v]:
                    key[v] = self.graph[u][v]
                    parent[v] = u

        self.print_res(parent)

def load_matrix(fileName):
    return np.loadtxt(fileName, dtype='i', delimiter=' ')

if __name__ == '__main__':
    minST1 = Graph(8)
    minST1.graph = load_matrix("m1.txt")
    minST1.prim()


