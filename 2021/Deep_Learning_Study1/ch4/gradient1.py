# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 17:13:06 2021

@author: ghqls
"""

import numpy as np
import matplotlib.pyplot as plt

def numerical_diff(f, x):
    # 수치 미분, 정의대로 => (f(x+h) - f(x)) / h => 부동소수점 문제 발생
    h = 1e-4
    return (f(x+h)-f(x-h)) / (2*h)

def func1(x):
    # f(x) = 0.01x^2 + 0.1x
    return 0.01*x*x + 0.1*x

def tanget1(f,x):
    d = numerical_diff(f, x)
    y = f(x) - d*x
    return lambda t : d*t + y

def func2(x):
    # f(x0,x1) = x0^2 + x1^2
    return np.sum(x**2)

# 편미분 벡터값 구하기 (gradient값 구하기)
def numerical_gradient(f, x):
    h = 1e-4
    grad = np.zeros_like(x)
    
    for idx in range(x.size):
        tmp_val = x[idx]
        
        #f(x+h)
        x[idx] = tmp_val + h
        fxh1 = f(x)
        
        #f(x-h)
        x[idx] = tmp_val - h
        fxh2 = f(x)
        
        grad[idx] = (fxh1 - fxh2) / (2*h)
        x[idx] = tmp_val
    
    return grad

#경사하강법
def gradient_descent(f, init_x, lr=0.01, step_num=100):
    x = init_x
    
    for i in range(step_num):
        grad = numerical_gradient(f, x)
        x -= lr*grad
    
    return x

x = np.arange(0.0,10.0,0.1)
y1 = func1(x)
tf = tanget1(func1,5.0)
y2 = tf(x)

plt.plot(x,y1)
plt.plot(x,y2)
plt.show()
