import numpy as np

with open('m1.txt', 'r') as f:
    graph = np.array([[int(num) for num in line.split()] for line in f])

n = graph.shape[0]

best_path = None
best_weight = float('inf')

def hamiltonian_cycle(path, weight):
    global best_path, best_weight

    if len(path) == n:
        if graph[path[-1], path[0]] != 0:
            weight += graph[path[-1], path[0]]
            if weight < best_weight:
                best_weight = weight
                best_path = path + [path[0]]
        return

    last_vertex = path[-1]
    for next_vertex in range(n):
        if graph[last_vertex, next_vertex] != 0 and next_vertex not in path:
            new_weight = weight + graph[last_vertex, next_vertex]
            if new_weight < best_weight:
                hamiltonian_cycle(path + [next_vertex], new_weight)

for start_vertex in range(n):
    hamiltonian_cycle([start_vertex], 0)

print(f"Найкоротший гамільтонів цикл: {best_path}")
print(f"Вага шляху: {best_weight}")
