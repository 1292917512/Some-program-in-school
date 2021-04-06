# -*- coding: UTF-8 -*-

"""
Created on 18-3-5
@summary: LeaderRank 节点排序算法
@author: hwk
"""
import networkx as nx
import numpy as np
from data_process.graph_process_function_old import *
from data_process.graph_process_function import Get_data

def leaderrank(graph):
    """
    节点排序
    :param graph:复杂网络图Graph
    :return: 返回节点排序值
    """
    # 节点个数
    num_nodes = graph.number_of_nodes()
    # 节点
    nodes = graph.nodes()
    # 在网络中增加节点g并且与所有节点进行连接
    graph.add_node(('NULL',('NULL','0.000')))
    for node in nodes:
        graph.add_edge(('NULL',('NULL','0.000')), node)
        graph.add_edge(node, ('NULL',('NULL','0.000')))
    # LR值初始化
    LR = {}
    for M in nodes:
        LR[M] = float(M[1][1])
    LR[('NULL',('NULL','0.000'))] = 0.0
    # 迭代从而满足停止条件
    while True:
        tempLR = {}
        for node1 in graph.nodes():
            s = 0.0
            for node2 in graph.nodes():
                if graph.has_edge(node2, node1):
                    s += 1.0 / graph.out_degree([node2])[node2] * LR[node2]
            tempLR[node1] = s
        # 终止条件:LR值不在变化
        error = 0.0
        for n in tempLR.keys():
            error += abs(tempLR[n] - LR[n])
        if error == 0.0:
            break
        LR = tempLR
        print("迭代中")
    # 节点g的LR值平均分给其它的N个节点并且删除节点
    print("结束1")
    avg = LR[0] / num_nodes
    LR.pop(0)
    for k in LR.keys():
        LR[k] += avg
    print("结束2")
    return LR




if __name__ == "__main__":
    import pandas as pd
    DIR = "E:\python_Object\GCN_Entity_Linking\data"  # 保存训练集和测试集的路径
    trainlist, testlist = Get_data(DIR)
    MGls = createGM(trainlist)

    i =0
    DIR = "E:\\python_Object\\GCN_Entity_Linking\\Generate_Graphfile_old\\"
    for GM in MGls:
        name = GM.artname.replace(' ', '')
        GM.matrix = np.loadtxt(DIR + name)
    # Generate_Graph(MGls)
        print("构建完毕")
    # demo1
    # Matrix = np.mat([[0,1,0,0,1,0],[0,0,1,0,0,0],[1,0,0,1,1,0],[0,1,0,0,0,1],[0,1,0,1,0,1],[1,0,0,0,0,0]])
    # graph = nx.from_numpy_matrix(Matrix,create_using=nx.DiGraph)
    # H = nx.relabel_nodes(graph,dict(enumerate(['user1','user2','user3','user4','user5','user6'])),copy=False)

    # demo2
    # Matrix = np.mat([[0,1,0,1],[0,0,1,1],[0,1,0,1],[0,1,1,0]])
        graph = nx.from_numpy_matrix(GM.matrix,create_using=nx.DiGraph)
        print("载入图")
        H = nx.relabel_nodes(graph,dict(enumerate(GM.vertices)),copy=False)
        print("图载入完毕,开始跑leaderrank")
        # print(leaderrank(graph,GM))
        # print("leadrrank完成")
        ls = sorted(leaderrank(graph).items(), key=lambda item: item[1])
        i=i+1;
        print(ls)
        if(i == 3):
            break


    # import matplotlib.pyplot as plt
    #
    # plt.figure()
    # nx.draw(graph, with_labels=True, font_color='#000000', node_color='r', font_size=8, node_size=20)
    # plt.show()

    # print sorted(leaderrank(graph).items(), key=lambda item: item[1])