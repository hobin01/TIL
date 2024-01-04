# -*- coding: utf-8 -*-
"""
Created on Wed Jan 13 01:54:09 2021

@author: ghqls
"""

class MulLayer:
    def __init__(self):
        self.x = None
        self.y = None
        
    def forward(self, x, y):
        self.x = x
        self.y = y
        out = x * y
        return out
    
    def backward(self, dout):
        dx = dout * self.y
        dy = dout * self.x
        
        return dx, dy
    
class AddLayer:
    def __init__(self):
        pass
    
    def forward(self, x, y):
        out = x + y
        return out
    
    def backward(self, dout):
        dx = dout * 1
        dy = dout * 1
        return dx, dy

apple = 100
apple_num = 2
orange = 150
orange_num = 3
tax = 1.1

# 가격 계산
mul_apple_layer = MulLayer()
mul_orange_layer = MulLayer()
add_apple_orange_layer = AddLayer()
mul_tax_layer = MulLayer()

mul_apple_price = mul_apple_layer.forward(apple, apple_num)
mul_orange_price = mul_orange_layer.forward(orange, orange_num)
add_apple_orange_price = add_apple_orange_layer.forward(mul_apple_price, mul_orange_price)
total_price = mul_tax_layer.forward(add_apple_orange_price, tax)

print("total_price={}".format(total_price))

# 미분 계산
dprice = 1
dapple_orange, dtax = mul_tax_layer.backward(dprice)
print("dprice={}, dapple_orange={}, dtax={}".format(dprice, dapple_orange, dtax))

dapple_mul, dorange_mul = add_apple_orange_layer.backward(dapple_orange)
print("dapple={}, dorange={}".format(dapple_mul, dorange_mul))

dapple, dapple_num = mul_apple_layer.backward(dapple_mul)
dorange, dorange_num = mul_orange_layer.backward(dorange_mul)

print("dapple={}, dapple_num={}, dorange={}, dorange_num={}".format(dapple, dapple_num, dorange, dorange_num))

