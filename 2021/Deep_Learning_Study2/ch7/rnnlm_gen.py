# -*- coding: utf-8 -*-
"""
Created on Sun Jan 31 01:59:29 2021

@author: ghqls
"""

import sys
sys.path.append('..')
import numpy as np
from common.functions import softmax
from ch6.rnnlm import Rnnlm
from ch6.better_rnnlm import BetterRnnlm

class RnnlmGen(Rnnlm):
    def generate(self, start_id, skip_ids=None, sample_size=100):
        word_ids = [start_id]
        x = start_id
        
        while len(word_ids) < sample_size:
            x = np.array(x).reshape(1,1)
            score = self.predict(x)
            p = softmax(score.flatten())
            
            sampled = np.random.choice(len(p), size=1, p=p)
            if (skip_ids is None) or (sampled not in skip_ids):
                x = sampled
                word_ids.append(int(x))
        
        return word_ids
    
    def get_state(self):
        return self.lstm_layer.h, self.lstm_layer.c
    
    def set_state(self, state):
        self.lstm_layer.set_state(*state)
        
        
        
class BetterRnnlmGen(BetterRnnlm):
    def generate(self, start_id, skip_ids=None, sample_size=100):
        word_ids = [start_id]
        x = start_id
        
        while len(word_ids) < sample_size:
            x = np.array(x).reshape(1,1)
            score = self.predict(x)
            p = softmax(score.flatten())
            
            sampled = np.random.choice(len(p), size=1, p=p)
            if (skip_ids is None) or (sampled not in skip_ids):
                x = sampled
                word_ids.append(int(x))
        
        return word_ids
    
    def get_state(self):
        states = []
        for layer in self.lstm_layer:
            states.append((layer.h, layer.c))
        return states
    
    def set_state(self, states):
        for layer, state in zip(self.lstm_layers, states):
            layer.set_state(*state)