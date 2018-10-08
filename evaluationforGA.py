#!/usr/bin/env python
# -*-coding:utf-8 -*-

import numpy as np
import random
import math
from decimal import Decimal
import GeneticAlgorithm as ga

length = 40

def create_genom(length):
    """
    引数で指定された桁のランダムな遺伝子情報を生成、格納したgenomClassで返します。
    :param length: 遺伝子情報の長さ
    :return: 生成した個体集団genomClass
    """
    genome_list = []
    for i in range(length):
        genome_list.append(random.randint(0, 1))
        #genome_list.append(1)
    return ga.genom(genome_list, 0)

def create_real_coordinate(ga):
    #各座標をarryに読み込む
    all_coordinate = np.loadtxt('grapemodel2018-1-7-23:17:54.csv',delimiter=',',dtype='float')
    genome_list = ga.getGenom()

    #残っている実だけのarrayを作る
    real_coordinate = np.zeros((0,3))
    for j in range(length):
        if genome_list[j] == 1:
            real_coordinate = np.vstack((real_coordinate , all_coordinate[j] ))

    return real_coordinate

def evaluation_d(ga):
    #D(X)
    Z=30
    genome = ga.getGenom()
    cuurent_fruits = 0

    for j in range(len(genome)):
        cuurent_fruits += genome[j]

    return abs(Z - cuurent_fruits)/Decimal(Z)


def evaluation_l(real_coordinate):
    #L(X)
    S=10
    z_max = real_coordinate.max(axis = 0)[2]
    z_min = real_coordinate.min(axis = 0)[2]
    cob_length = abs(z_max - z_min)

    return abs(S - cob_length)/S


def evaluation_g(real_coordinate):
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

    return abs(R-g)/R


if __name__ == '__main__':
    #現行個体を生成
    genome_list = create_genom(length) #遺伝子情報のリスト
    print(genome_list.getGenom())

    real_coordinate = create_real_coordinate(genome_list)
    print(real_coordinate)

    D = evaluation_d(genome_list)
    L = evaluation_l(real_coordinate)
    G = evaluation_g(real_coordinate)

    print("D=",D)
    print("L=",L)
    print("G=",G)
