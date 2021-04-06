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
from data_process.graph_process_function import Get_data,createGM
# from sklearn.datasets.samples_generator import make_blobs
# import pandas as pd
# import copy


from Graph_and_Matrix.layers import processAdj
from Graph_and_Matrix.models import GCN,GCN2

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


# def train(data,data_loss,args,model,loss_fn):
#     # loss_fn = torch.nn.MSELoss(reduction='sum')
#     f = torch.eye(1500)
#     f = torch.Tensor(f)
#     f = torch.Tensor(f).to(args.device)
#     for epoch in range(args.epoch):
#         sum_loss = 0
#         c_num = 0
#         count = 0
#         for _ in data.filels:
#             adj = np.loadtxt(data.Graph_dir + '\\' + _)
#             y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
#             y = torch.LongTensor(y)
#             adj = normalize_adj(adj)
#             for start in range(0, len(f), args.batchsize):
#                 end = start + args.batchsize
#                 X = f[start:end].to(args.device)
#                 Y = y[start:end].to(args.device)
#                 if (torch.max(Y) < 1):
#                     continue
#                 # Y = torch.sum(Y,dim=1)
#                 # Y = Y.reshape((1,args.batchsize))
#                 # Y = torch.max(Y, dim=1)[1]
#                 outputs = model(X,adj)
#                 print(outputs)
#                 predicted = torch.max(outputs.data, dim = 1)[1]
#                 print(predicted)
#                 print(Y)
#                 print('\n')
#                 correct = (predicted == Y).sum().item()
#                 loss = loss_fn(outputs,Y)
#                 loss.backward()
#                 optimizer.step()
#                 sum_loss += float(loss)
#                 if (correct == 30):
#                     c_num = c_num + 1
#                 count = count + 1
#             print("Accuracy on test set: {:.2%}".format(c_num / count))
#         print("Accuracy on test set: {:.2%}".format(c_num / count))
#         print("epoch:{}\tloss: {}".format(epoch, sum_loss / count))

def train(data,data_loss,args,model,loss_fn,dir_Similarity,dir_f,dmb=False):
    aim = args.batchsize
    # loss_fn = torch.nn.MSELoss(reduction='sum')
    # f = torch.eye(1500)
    # f = torch.Tensor(f).to(args.device)
    for epoch in range(args.epoch):
        sum_loss = 0
        c_num = 0
        count = 0
        for _ in data.filels:
            print(_+":")
            f = np.loadtxt(dir_f+_)
            f = torch.Tensor(f).to(args.device)
            adj2 = np.loadtxt(dir_Similarity+_)
            adj2 = np.diag(adj2)
            adj2 = torch.FloatTensor(adj2)
            adj = np.loadtxt(data.Graph_dir + '\\' + _)
            y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
            y = torch.LongTensor(y)
            adj = normalize_adj(adj)
            for start in range(0, len(f), args.batchsize):
                end = start + args.batchsize
                # X = f[start:end].to(args.device)
                Y = y[start:end].to(args.device)
                ADJ = adj[start:end].to(args.device)
                ADJ2 = adj2[start:end].to(args.device)
                RE = torch.sum(ADJ.t(), dim=0)
                if (torch.max(Y) < 1):
                    continue
                #是否开启单目标
                if(dmb):
                    aim = 1
                    # Y = torch.sum(Y,dim=1)
                    Y = Y.reshape((1,args.batchsize))
                    Y = torch.max(Y, dim=1)[1]
                outputs = model(f,adj,ADJ2)
                print(outputs)
                print(RE)
                predicted = torch.max(outputs.data, dim = 1)[1]
                print(predicted)
                print(Y)
                print('\n')
                correct = (predicted == Y).sum().item()
                loss = loss_fn(outputs,Y)
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
                sum_loss += float(loss)
                if(correct==aim):
                    c_num = c_num+1
                count=count+1
            print("Accuracy on test set: {:.2%}".format(c_num / count))
        print("Accuracy on test set: {:.2%}".format(c_num/count))
        print("epoch:{}\tloss: {}".format(epoch, sum_loss / count))



def test(data,data_loss,args,model,loss_fn,dir_Similarity,dir_f,aim_dir,dmb=False):
    aim = args.batchsize
    # f = torch.eye(1500)
    # f = torch.Tensor(f).to(args.device)
    with torch.no_grad():
        model.train()
        for epoch in range(args.epoch):
            sum_loss = 0
            c_num = 0
            count = 0
            for _ in data.filels:
                dir = aimdir + _
                file = open(dir, 'w', newline="")
                print("文章{}候选：".format(_))
                f = np.loadtxt(dir_f+_)
                f = torch.Tensor(f).to(args.device)
                adj2 = np.loadtxt(dir_Similarity + _)
                adj2 = np.diag(adj2)
                adj2 = torch.FloatTensor(adj2)
                adj = np.loadtxt(data.Graph_dir + '\\' + _)
                y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
                y = torch.LongTensor(y)
                adj = normalize_adj(adj)
                i =1
                for start in range(0, len(f), args.batchsize):
                    end = start + args.batchsize
                    Y = y[start:end].to(args.device)
                    ADJ = adj[start:end].to(args.device)
                    ADJ2 = adj2[start:end].to(args.device)
                    RE = torch.sum(ADJ.t(), dim=0)
                    if (torch.max(Y) < 1):
                        continue
                    if (dmb):
                        aim = 1
                        # Y = torch.sum(Y,dim=1)
                        Y = Y.reshape((1, args.batchsize))
                        Y = torch.max(Y, dim=1)[1]
                    outputs = model(f,adj,ADJ2)
                    print(outputs)
                    print(RE)
                    predicted = torch.max(outputs.data, dim=1)[1]
                    print("第{}个指称预测为：{} 实际为：{}".format(i,predicted,Y))
                    i = i+1
                    correct = (predicted == Y).sum().item()
                    print(predicted)
                    print(Y)
                    print('\n')
                    loss = loss_fn(outputs, Y)
                    sum_loss += float(loss)
                    if (correct == aim):
                        c_num = c_num + 1
                    count = count + 1
                    a = Y.to("cpu").tolist()[0]
                    file.write(str(a)+" ")
                file.close()
                print("Accuracy on test set: {:.2%}".format(c_num / count))
            print("Accuracy on test set: {:.2%}".format(c_num / count))
            print("epoch:{}\tloss: {}".format(epoch, sum_loss / count))



def test_adj(data,data_loss,args):
    # f = torch.eye(1500)
    # f = torch.Tensor(f)
    # f = torch.Tensor(f).to(args.device)
    sum_loss = 0
    c_num = 0
    count = 0
    for _ in data.filels:
        adj = np.loadtxt(data.Graph_dir + '\\' + _)
        print(data.Graph_dir + '\\' + _)
        y = np.loadtxt(data_loss.Graph_dir + '\\' + _)
        print(data_loss.Graph_dir + '\\' + _)
        y = torch.Tensor(y)
        adj = torch.Tensor(adj)
        for start in range(0, len(y), args.batchsize):
            end = start + args.batchsize
            ADJ = adj[start:end].to(args.device)
            Y = y[start:end].to(args.device)
            if (torch.max(Y) < 1):
                continue
            # Y = torch.sum(Y,dim=1)

            ADJ = ADJ.reshape((1, args.batchsize))
            ADJ = torch.sum(ADJ,dim=1)

            ADJ=ADJ.reshape((1, 1500))
            print(ADJ)
            # ADJ = torch.max(ADJ,dim=1)[1]
            Y = Y.reshape((1, 1500))
            print(Y)
            # Y = torch.max(Y, dim=1)[1]
            print("\n")



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
    parser = argparse.ArgumentParser()
    parser.add_argument("--c", type=float, default=0.01)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--batchsize", type=int, default=30)
    parser.add_argument("--epoch", type=int, default=30)
    parser.add_argument("--device", default="cuda", choices=["cpu", "cuda"])
    parser.add_argument('--dropout', type=float, default=0.7,
                        help='Dropout rate (1 - keep probability).')
    parser.add_argument("--bert", type=bool, default=True)
    parser.add_argument("--gmissm",type=bool,default=False)
    args = parser.parse_args()
    args.device = torch.device(args.device if torch.cuda.is_available() else "cpu")
    DIR = "E:\python_Object\GCN_Entity_Linking\data"  # 保存训练集和测试集的路径
    DIR_feature = "E:\\python_Object\\GCN_Entity_Linking\\data\\feature\\" #特征向量位置
    DIR_feature2 = "E:\\python_Object\\GCN_Entity_Linking\\data\\feature2\\" #特征向量位置
    DIR_loss = "E:\\python_Object\\GCN_Entity_Linking\\data\\gm_loss\\"
    data_loss = GraphDataset(DIR_loss)
    DIR_Similarity_bert = "E:\\python_Object\\GCN_Entity_Linking\\data\\sm_bert\\"  #bert相似度
    DIR_Similarity_unbert = "E:\\python_Object\\GCN_Entity_Linking\\data\\sm_bert\\"  #非 bert相似度


    model = GCN2(nfeat=1500, nhid=1500, nhid2=30, nclass=30, nclass2=1, dropout=args.dropout)
    # model = GCN(nfeat=1500,nhid=1500,nhid2 = 30,nclass=30,nclass2=1,dropout=args.dropout)
    model.to(args.device)
    optimizer = optim.SGD(model.parameters(), lr=args.lr)
    loss_fn = torch.nn.CrossEntropyLoss()
    model.train()
    # model=torch.load(".\\model\\model_testab_bert_wikiadj")
    # args.epoch = 1
    smlis =['ace2004\\','aquaint\\','clueweb\\','msnbc\\','testa\\','testab\\','testb\\','wikipedia\\','tain\\']
    #训练集合Graph_dir = {str} 'E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_wiki\\wiki_msnbc\\'
    if(args.gmissm):
        dir ="E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_sm\\wned-"
    else:
        dir =  "E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_wiki\\wiki_"

    # dir2 = "E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_sm_wiki\\"
    # data =  GraphDataset(dir2 + smlis[3])
    # data = GraphDataset(dir+smlis[4])
    data = GraphDataset("E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_sm_wiki\\testab\\")
    # test_adj(data,data_loss,args)
    train(data,data_loss,args,model,loss_fn,DIR_Similarity_bert,DIR_feature,True)
    # torch.save(model,".\\model\\model_testab_bert_wikiadj")
    # aimdir = "E:\\python_Object\\GCN_Entity_Linking\\data\\result\\result_bert_sm\\"
    # test(data,data_loss,args,model,loss_fn,DIR_Similarity_bert,DIR_feature,aimdir,True)
    # ls = test(data,data_loss,args)