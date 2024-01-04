# -*- coding: utf-8 -*-
"""
Created on Thu Jan 21 20:44:55 2021

@author: ghqls
"""

import numpy as np
import matplotlib.pyplot as plt
import sys, os
sys.path.append('..')
from dataset import spiral

x, t = spiral.load_data()
print('x', x.shape)
print('t', t.shape)

n = 100
cls_num = 3
markers = ['o', 'x', '^']

for i in range(cls_num):
    plt.scatter(x[i * n : (i+1) * n, 0], x[i * n : (i+1) * n, 1], marker=markers[i])
plt.show()