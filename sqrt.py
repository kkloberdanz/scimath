import math
import time
import numpy as np

size = 100000001
print('building list')
a = [float(i) for i in range(size)]

print('sqrt-ing')
start = time.time()
for i in range(len(a)):
    a[i] = math.sqrt(i)
finish = time.time()
print(a[size - 1])
print('runtime:', 1000 * (finish - start), 'ms')

del a

print('building np array')
arr = np.array([float(i) for i in range(size)])
print('sqrt-ing')
start = time.time()
b = np.sqrt(arr)
finish = time.time()
print(b[size - 1])
print('runtime:', 1000 * (finish - start), 'ms')
