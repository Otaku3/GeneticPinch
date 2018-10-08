#!/usr/bin/env python
# -*-coding:utf-8 -*-

import numpy as np
import random
import math
length = 40

genome_list = [] #遺伝子情報のリスト
for i in range(length):
    #genome_list.append(random.randint(0, 1))
    genome_list.append(1)
print(genome_list)

#各座標をarryに読み込む
all_coordinate = np.loadtxt('grapemodel2018-1-7-23:17:54.csv',delimiter=',',dtype='float')
#print(all_coordinate)


#残っている実だけのarrayを作る
real_coordinate = np.zeros((0,3))
for j in range(length):
    if genome_list[j] == 1:
        real_coordinate = np.vstack((real_coordinate , all_coordinate[j] ))
print(real_coordinate)

#D(X)
Z=30
cuurent_fruits = 0
for j in range(length):
    cuurent_fruits += genome_list[j]
print("D(X)=",abs(Z - cuurent_fruits))
print("Normalized_D(X)=",abs(Z - cuurent_fruits)/Z)

#L(X)
S=10
z_max = real_coordinate.max(axis = 0)[2]
z_min = real_coordinate.min(axis = 0)[2]
cob_length = abs(z_max - z_min)
print("L(X)=",abs(S - cob_length))
print("Normalized_L(X)=",abs(S - cob_length)/S)

#G(X)
R = 1 #理想重心距離＝実の直径
D = 0 #全ての実の近傍実との平均距離の総和
g = 0 #g(x)
for j in range(len(real_coordinate)):
    d_sum = 0 #実jの近傍実との距離の総和
    k_count = 0 #実jの近傍実の数
    for k in range(len(real_coordinate)):
        d = 0
        if j != k:
            d = math.sqrt( math.pow( (real_coordinate[k][0]-real_coordinate[j][0]) , 2 )
                          +math.pow( (real_coordinate[k][1]-real_coordinate[j][1]) , 2 )
                          +math.pow( (real_coordinate[k][2]-real_coordinate[j][2]) , 2 ) )
        if d < R:
            d_sum += d
            k_count += 1

    if k_count != 0:
        D += d_sum/k_count
g = D/len(real_coordinate)
print("G(X)=",abs(R-g))
print("Normalized_G(X)=",abs(R-g)/R)
