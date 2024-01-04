# -*- coding: utf-8 -*-
"""
Created on Tue Jan 26 23:22:52 2021

@author: ghqls
"""

import sys
sys.path.append('..')
import numpy as np
from common.layers import MatMul, SoftmaxWithLoss

class SimpleSkipGram:
    def __init__(self, vocab_size, hidden_size):
        V, H = vocab_size, hidden_size
        
        W_in = 0.01 * np.random.randn(V, H).astype('f')
        W_out = 0.01 * np.random.randn(H, V).astype('f')
        
        self.in_layer = MatMul(W_in)
        self.out_layer = MatMul(W_out)
        self.loss_layer1 = SoftmaxWithLoss()
        self.loss_layer2 = SoftmaxWithLoss()
        
        layers = [self.in_layer, self.out_layer]
        self.params, self.grads = [], []
        
        for layer in layers:
            self.params += layer.params
            self.grads += layer.grads
            
        self.word_vecs = W_in
        
    def forward(self, contexts, target):
        h = self.in_layer.forward(target)
        s = self.out_layer.forward(h)
        loss1 = self.loss_layer1.forward(s, contexts[:, 0])
        loss2 = self.loss_layer2.forward(s, contexts[:, 1])
        loss = loss1 + loss2
        
        return loss
    
    def backward(self, dout=1):
        dloss1 = self.loss_layer1.backward(dout)
        dloss2 = self.loss_layer2.backward(dout)
        ds = dloss1 + dloss2
        dh = self.out_layer.backward(ds)
        self.in_layer.backward(dh)
        
        return None
    