from collections import defaultdict
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)
        self.visited_edges = defaultdict(bool)

    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def removeEdge(self, u, v):
        self.graph[u].remove(v)
        self.graph[v].remove(u)
        self.visited_edges[(u, v)] = True
        self.visited_edges[(v, u)] = True

    def DFSUtil(self, v, visited):
        visited[v] = True

        for i in self.graph[v]:
            if visited[i] == False:
                self.DFSUtil(i, visited)

    def isConnected(self):
        visited = [False] * (self.V)

        for i in range(self.V):
            if len(self.graph[i]) != 0:
                break

        if i == self.V - 1:
            return True

        self.DFSUtil(i, visited)

        for i in range(self.V):
            if visited[i] == False and len(self.graph[i]) > 0:
                return False

        return True

    def isEulerian(self):
        if self.isConnected() == False:
            return 0
        else:
            odd = 0
            for i in range(self.V):
                if len(self.graph[i]) % 2 != 0:
                    odd += 1

            if odd == 0:
                return 2
            elif odd == 2:
                return 1
            elif odd > 2:
                return 0

    def EulerCycle(self):
        start_vertex = list(self.graph.keys())[0]

        stack = [start_vertex]
        cycle = []
        visited_edges = defaultdict(bool)

        while stack:
            v = stack[-1]

            if self.graph[v]:
                u = self.graph[v][0]
                if visited_edges[(v, u)] == False:
                    visited_edges[(v, u)] = True
                    visited_edges[(u, v)] = True
                    stack.append(u)
                    self.graph[v].remove(u)
                    self.graph[u].remove(v)
                else:
                    self.graph[v].remove(u)
                    self.graph[u].remove(v)
            else:
                cycle.append(stack.pop()+1)

        return cycle[::-1]

    def printEulerCycle(self):
        print(self.EulerCycle())

    def EulerPath(self):
        start_vertex = list(self.graph.keys())[0]
        for i in range(self.V):
            if len(self.graph[i]) % 2 != 0:
                start_vertex = i
                break

        path = []
        stack = [(start_vertex, None)]
        visited_edges = set()

        while stack:
            v, prev = stack[-1]

            if self.graph[v]:
                u = self.graph[v][0]
                edge = tuple(sorted((v, u)))
                if edge not in visited_edges:
                    stack.append((u, edge))
                    self.graph[v].remove(u)
                    self.graph[u].remove(v)
                    visited_edges.add(edge)
            else:
                path.append(stack.pop()[0] + 1)

        return  path[::-1]

    def printEulerPath(self):
        print(self.EulerPath())

    def test(self):
        res = self.isEulerian()
        if res == 0:
            print("Graph is not Eulerian.")
        elif res == 1:
            print("Graph has an Euler path:")
            self.printEulerPath()
        else:
            print("Graph has an Euler cycle:")
            self.printEulerCycle()

def draw_matrix(matrix):
    G = nx.Graph(matrix)

    nx.draw(G, with_labels=True)
    plt.show()

def get_edges(matrix):
    edges = []

    for i in range(len(matrix)):
        for j in range(i, len(matrix[i])):
            if matrix[i][j] != 0:
                edges.append((i, j))
    return edges

def load_matrix(fileName):
    return np.loadtxt(fileName, dtype='i', delimiter=' ')

if __name__ == '__main__':
    m = load_matrix("m1.txt")
    edges = get_edges(m)
    g = Graph(8)
    for edge in edges:
        g.addEdge(edge[0], edge[1])
    g.test()

    draw_matrix(m)
