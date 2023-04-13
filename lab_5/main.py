import itertools
import numpy as np

def isomorphic(matrix1_file, matrix2_file):
    m1 = np.loadtxt(matrix1_file)
    m2 = np.loadtxt(matrix2_file)
    return isomorphic_from_matrices(m1, m2)

def isomorphic_from_matrices(A, B):
    n = A.shape[0]
    if B.shape[0] != n:
        return False
    for p in itertools.permutations(range(n)):
        P = np.zeros((n, n))
        for i in range(n):
            P[i, p[i]] = 1
        if np.array_equal(A @ P, P @ B):
            return True
    return False

if isomorphic('m1.txt', 'm2.txt'):
    print('The graphs are isomorphic')
else:
    print('The graphs are not isomorphic')