# -*- coding: utf-8 -*-
"""
Created on Sat Jan 16 21:59:57 2021

@author: ghqls
"""

import numpy as np
import matplotlib.pyplot as plt

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def ReLU(x):
    return np.maximum(0, x)

def tanh(x):
    return np.tanh(x)

x = np.random.randn(1000, 100) # (1000, 100) matrix 평균 0, 표준편차 1인 정규분포
node_num = 100 # 각 은닉층의 노드 개수
hidden_layer_size = 5 # 은닉층 개수
activations = {} # 활성화 결과

for i in range(hidden_layer_size):
    if i!=0:
        x = activations[i-1]
    
    # w = np.random.randn(node_num, node_num) * 0.01 # 표준편차 0.01
    # w = np.random.randn(node_num, node_num) * (1 / np.sqrt(node_num)) # Xavier 초기값, 표준편차 = sqrt(앞 층 노드) 
    w = np.random.randn(node_num, node_num) * (2 / np.sqrt(node_num)) # HE 초기값, ReLU일 때 적합
    
    a = np.dot(x, w)
    
    # z = sigmoid(a)
    # z = tanh(a)
    z = ReLU(a)
    
    activations[i] = z

for i, a in activations.items():
    plt.subplot(1, len(activations), i+1)
    plt.title(str(i+1)+"-layer")
    plt.hist(a.flatten(), 30, range=(0,1))

plt.show()

