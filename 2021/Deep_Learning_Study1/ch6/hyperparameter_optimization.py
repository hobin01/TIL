# -*- coding: utf-8 -*-
"""
Created on Sun Jan 17 01:35:30 2021

@author: ghqls
"""

import sys, os
sys.path.append(os.pardir)
import numpy as np
import matplotlib.pyplot as plt
from dataset.mnist import load_mnist
from common.multi_layer_net import MultiLayerNet
from common.util import shuffle_dataset
from common.trainer import Trainer

(x_train, t_train), (x_test, t_test) = load_mnist(normalize=True)

x_train = x_train[:500]
t_train = t_train[:500]

validation_rate = 0.2
validation_num = int(x_train.shape[0] * validation_rate)
x_val = x_train[:validation_num]
t_val = t_train[:validation_num]
x_train = x_train[validation_num:]
t_train = t_train[validation_num:]

def __train(lr, weight_decay, epocs=50):
    network = MultiLayerNet(input_size=784, hidden_size_list=[100,100,100,100,100,100],
                            output_size=10, weight_decay_lambda=weight_decay)
    trainer = Trainer(network, x_train, t_train, x_val, t_val,
                      epochs=epocs, mini_batch_size=100, optimizer='sgd',
                      optimizer_param={'lr':lr}, verbose=False)
    trainer.train()
    return trainer.test_acc_list, trainer.train_acc_list

optimization_trial = 100
results_val = {}
results_train = {}

for _ in range(optimization_trial):
    weight_decay = 10 ** np.random.uniform(-8,-4)
    lr = 10 ** np.random.uniform(-6,-2)
    
    val_acc_list, train_acc_list = __train(lr, weight_decay)
    key = "lr:"+str(lr)+", weight_decay:"+str(weight_decay)
    results_val[key] = val_acc_list
    results_train[key] = train_acc_list
    
graph_draw_num = 20
col_num = 5
row_num = int(np.ceil(graph_draw_num / col_num))
idx = 0

for key, val_acc_list in sorted(results_val.items(), key=lambda x:x[1][-1], reverse=True):
    plt.subplot(row_num, col_num, idx+1)
    plt.title("Best-"+str(idx+1))
    if idx % 5:
        plt.yticks([])
    plt.xticks([])
    x = np.arange(len(val_acc_list))
    plt.plot(x, val_acc_list)
    plt.plot(x, results_train[key],"--")
    idx += 1
    
    if idx >= graph_draw_num:
        break

plt.show()
