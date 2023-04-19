import numpy as np

matrix = np.loadtxt("m1.txt", dtype=int)

def ford_fulkerson(matrix, source, sink):
    flow_matrix = np.zeros_like(matrix)

    while True:
        path = bfs(matrix, flow_matrix, source, sink)

        if path is None:
            break

        flow = min(matrix[u][v] - flow_matrix[u][v] for u, v in path)

        for u, v in path:
            flow_matrix[u][v] += flow
            flow_matrix[v][u] -= flow

    max_flow = sum(flow_matrix[source][i] for i in range(len(matrix)))

    return max_flow

def bfs(matrix, flow_matrix, s, t):
    queue = [s]
    visited = [False] * len(matrix)
    paths = {s: []}
    visited[s] = True

    while queue:
        u = queue.pop(0)
        for v in range(len(matrix)):
            if not visited[v] and matrix[u][v] - flow_matrix[u][v] > 0:
                visited[v] = True
                paths[v] = paths[u] + [(u, v)]
                if v == t:
                    return paths[v]
                queue.append(v)
    return None

max_flow = ford_fulkerson(matrix, 0, len(matrix)-1)

print("Максимальний потік у графі:", max_flow)

