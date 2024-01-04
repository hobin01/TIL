# -*- coding: utf-8 -*-
"""
Created on Tue Jan 12 16:59:15 2021

@author: ghqls
"""

import sys, os
sys.path.append(os.pardir)
from common.functions import *
from common.gradient import numerical_gradient

class TwoLayerNet: # 2층 신경망, input_size = 입력층 노드 수, hidden_size = 은닉층 노드 수, output_size = 출력층 노드 수
    def __init__(self, input_size, hidden_size, output_size, weight_init_std=0.01):
        self.params = {}
        self.params['W1'] = weight_init_std * np.random.randn(input_size, hidden_size) # 1층의 가중치
        self.params['b1'] = np.zeros(hidden_size) #1층의 편향
        self.params['W2'] = weight_init_std * np.random.randn(hidden_size, output_size) # 2층의 가중치
        self.params['b2'] = np.zeros(output_size) # 2층의 편향
        
    def predict(self, x): # x : MNIST 이미지 데이터, predict = 2층 신경망 추론 결과 도출
        W1, W2 = self.params['W1'], self.params['W2']
        b1, b2 = self.params['b1'], self.params['b2']
        
        a1 = np.dot(x, W1) + b1 # 데이터와 가중치, 편향 연산 (1층)
        z1 = sigmoid(a1) # 활성화 함수 : 시그모이드
        a2 = np.dot(z1, W2) + b2 # 데이터와 가중치, 편향 연산 (2층)
        y = softmax(a2)  # 출력함수 : 소프트맥스
        
        return y
    
    def loss(self, x, t): # x : 이미지데이터, t : 정답 레이블, loss : 손실함수 계산
        y = self.predict(x)
        
        return cross_entropy_error(y, t)
    
    def accuracy(self, x, t): # accuracy : 정확도 계산
        y = self.predict(x)
        y = np.argmax(y, axis=1)
        t = np.argmax(t, axis=1)
        
        accuracy = np.sum(y==t) / float(x.shape[0])
        return accuracy
    
    def numerical_gradient(self, x, t): # 가중치, 편향의 기울기 계산
        loss_W = lambda W: self.loss(x,t)
        
        grads = {} # 기울기 값 저장
        grads['W1'] = numerical_gradient(loss_W, self.params['W1']) # 1층의 가중치의 기울기
        grads['b1'] = numerical_gradient(loss_W, self.params['b1']) # 1층의 편향의 기울기
        grads['W2'] = numerical_gradient(loss_W, self.params['W2']) # 2층의 가중치의 기울기
        grads['b2'] = numerical_gradient(loss_W, self.params['b2']) # 2층의 편향의 기울기
        
        return grads
    
    def gradient(self, x, t): # 기울기 계산 성능 개선
        W1, W2 = self.params['W1'], self.params['W2']
        b1, b2 = self.params['b1'], self.params['b2']
        
        grads = {}
        
        batch_num = x.shape[0]
        
        # 앞에서부터
        a1 = np.dot(x, W1) + b1
        z1 = sigmoid(a1)
        a2 = np.dot(z1, W2) + b2
        y = softmax(a2)
        
        # 뒤에서부터
        dy = (y - t) / batch_num
        grads['W2'] = np.dot(z1.T, dy)
        grads['b2'] = np.sum(dy, axis=0)
        
        da1 = np.dot(dy, W2.T)
        dz1 = sigmoid_grad(a1) * da1
        grads['W1'] = np.dot(x.T, dz1)
        grads['b1'] = np.sum(dz1, axis=0)
        
        return grads
        
        