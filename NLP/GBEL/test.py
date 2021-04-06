# import numpy as np
# import torch
from data_process.utils import GraphDataset
import argparse
# import torch.nn.functional as F
# import matplotlib.pyplot as plt
import numpy as np
import torch
# import torch.nn as nn
import torch.optim as optim
import os
from data_process.graph_process_function import Get_data
# from sklearn.datasets.samples_generator import make_blobs
# import pandas as pd
# import copy

from Graph_and_Matrix.layers import processAdj
from Graph_and_Matrix.models import *

import scipy.sparse as sp


def normalize_adj(adj):
    adj = adj + np.eye(adj.shape[0])  # 加入自环
    # adj = adj.to_dense().cpu().numpy()
    adj = sp.coo_matrix(adj)  # 构建张量
    rowsum = np.array(adj.sum(1))  # 每行的数加在一起
    d_inv_sqrt = np.power(rowsum, -0.5).flatten()  # 输出rowsum ** -1/2
    d_inv_sqrt[np.isinf(d_inv_sqrt)] = 0.  # 溢出部分赋值为0
    d_mat_inv_sqrt = sp.diags(d_inv_sqrt)  # 对角化
    adj = adj.dot(d_mat_inv_sqrt).transpose().dot(d_mat_inv_sqrt).tocoo()  # 转置后相乘
    return torch.FloatTensor(adj.todense()).cuda()

# def test(X,Y,model,args):
#     X = torch.Tensor(X)
#     Y = torch.LongTensor(np.where(Y)[1])
#     correct = 0
#     total = 0
#     with torch.no_grad(): # 不会再进行梯度
#         for start in range(0, len(X), args.batchsize):
#             end = start + args.batchsize
#             x = X[start:end].to(args.device)
#             y = Y[start:end].to(args.device)
#             outputs = model(x)
#             _, predicted = torch.max(outputs.data, dim=1)
#             total+=y.size(0)
#             correct+=(predicted==y).sum().item()
#     print("Accuracy on test set: %d %%" % (100 * correct / total))


import torch.nn.functional as F
DIR_Graph = "E:\\python_Object\\GCN_Entity_Linking\\data_Graphfile"  #保存对应图数据的路径
DIR_Graph_loss = "E:\\python_Object\\GCN_Entity_Linking\\data_Graphfile_loss_M"
DIR_Graph_M = "E:\\python_Object\\GCN_Entity_Linking\\data_Graphfile_loss_M"
DIR_Graph_t = "/data_Graphfile_testA"  #保存对应图数据的路径
DIR_Graph_loss_t = "E:\\python_Object\\GCN_Entity_Linking\\data_Graphfile_loss_testA"



def train(data,data_loss,args,trainlist):
    model = GCN1(nfeat=30,nhid=1500,nclass=30,dropout=args.dropout)
    model.to(args.device)
    optimizer = optim.SGD(model.parameters(), lr=args.lr)
    # loss_fn = torch.nn.CrossEntropyLoss()
    loss_fn = torch.nn.MSELoss(reduction='sum')
    f = torch.eye(1500)
    f = torch.Tensor(f)
    f = torch.Tensor(f).to(args.device)
    model.train()
    for epoch in range(args.epoch):
        sum_loss = 0
        c_num = 0
        count = 0
        for _ in data.filels:
            adj = np.loadtxt(data.Graph_dir + '\\' + _)
            y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
            y = torch.Tensor(y)
            adj = normalize_adj(adj)
            for start in range(0, len(f), args.batchsize):
                end = start + args.batchsize
                X = f[start:end].to(args.device)
                Y = y[start:end].to(args.device)
                if (torch.max(Y) < 1):
                    continue
                Y = torch.sum(Y,dim=1)
                # Y = Y.reshape((1,args.batchsize))
                # Y = torch.max(Y, dim=1)[1]
                outputs = model(X,adj)
                print(outputs)
                predicted = torch.max(outputs.data, dim = 1)[1]
                print(predicted)
                print(Y)
                print('\n')
                # correct = (predicted == Y).sum().item()
                loss = loss_fn(outputs,Y)
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
                sum_loss += float(loss)
                # if(correct==1):
                #     c_num = c_num+1
                count=count+1
            print("Accuracy on test set: {:.2%}".format(c_num / count))
        print("Accuracy on test set: {:.2%}".format(c_num/count))
        print("epoch:{}\tloss: {}".format(epoch, sum_loss / count))



def test(datapath,data_loss, model,args):
        correct = 0
        total = 0
        root,dirs,file = os.walk(datapath)
        f = torch.eye(1500)
        f = torch.Tensor(f)
        f = torch.Tensor(f).to(args.device)
        with torch.no_grad():
            for _ in file:
                adj = np.loadtxt( datapath+ '\\' + _)
                y = np.loadtxt( data_loss+ '\\' + _)
                y = torch.LongTensor(y)
                adj = normalize_adj(adj)
                for start in range(0, len(f), args.batchsize):
                    end = start + args.batchsize
                    X = f[start:end].to(args.device)
                    Y = y[start:end].to(args.device)
                    if (torch.max(Y) < 1):
                        continue
                    Y = Y.reshape((1, args.batchsize))
                    Y = torch.max(Y, dim=1)[1]
                    outputs = model(X, adj)
                    print(outputs)
                    predicted = torch.max(outputs.data, dim=0)[1]
                    print(predicted)
                    print(Y)
                    print('\n')
                    total += y.size(0)
                    correct += (predicted == y).sum().item()
        print("Accuracy on test set: %d %%" % (100 * correct / total))


# def test(data, data_loss, model, args,):
#     correct = 0
#     total = 0
#     ls =[]
#     ls_index = []
#     with torch.no_grad():
#         for _ in data.filels:
#             x = np.loadtxt(data.Graph_dir + '\\' + _)
#             y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
#             adj = torch.Tensor(x).to(args.device)
#             adj = processAdj(adj)
#             y = torch.LongTensor(y).to(args.device)
#             outputs = model(f,adj)
#             print(outputs)
#             _, predicted = torch.max(outputs.data, dim=1)
#             print(predicted)
#             print(y)
#             ls.append(copy.deepcopy(ls_index))
#             ls_index.clear()
#             total += y.size(0)
#             correct += (predicted == y).sum().item()
#     print("Accuracy on test set: %d %%" % (100 * correct / total))
#     return ls



if __name__ == "__main__":

    DIR = "E:\python_Object\GCN_Entity_Linking\data"  # 保存训练集和测试集的路径
    # # DIR_Graph = "D:\python_Object\GCN_Entity_Linking\Graph_data"  # 保存对应图数据的路径
    trainlist,testlist = Get_data(DIR)
    parser = argparse.ArgumentParser()
    parser.add_argument("--c", type=float, default=0.01)
    parser.add_argument("--lr", type=float, default=1e-5)
    parser.add_argument("--batchsize", type=int, default=30)
    parser.add_argument("--epoch", type=int, default=1)
    parser.add_argument("--device", default="cuda", choices=["cpu", "cuda"])
    parser.add_argument('--dropout', type=float, default=0.5,
                        help='Dropout rate (1 - keep probability).')
    args = parser.parse_args()
    args.device = torch.device(args.device if torch.cuda.is_available() else "cpu")
    data = GraphDataset(DIR_Graph)
    data_loss = GraphDataset(DIR_Graph_loss)
    train(data,data_loss,args,trainlist)

    # ls = test(data,data_loss,args)


