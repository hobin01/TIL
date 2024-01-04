# -*- coding: utf-8 -*-
"""
Created on Sun Jan 24 21:56:39 2021

@author: ghqls
"""

import numpy as np

def ppmi(C, verbose=False, eps=1e-8):
    M = np.zeros_like(C, dtype=np.float32)
    N = np.sum(C)
    S = np.sum(C, axis=0)
    total = C.shape[0] * C.shape[1]
    cnt = 0
    
    for i in range(C.shape[0]):
        for j in range(C.shape[1]):
            pmi = np.log2(C[i,j]*N / (S[j]*S[i]) + eps)
            M[i,j] = max(0, pmi)
            
            if verbose:
                cnt += 1
                if(cnt % (total//100) == 0):
                    print("%.1f%% 완료" %(100*cnt/total))
    
    return M