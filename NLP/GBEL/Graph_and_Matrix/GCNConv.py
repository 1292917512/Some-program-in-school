import math
import torch
from torch.nn.parameter import Parameter
from torch import nn
import numpy as np
import torch.nn.functional as F
class GraphConv(nn.Module):
    def __init__(self, in_features, out_features, bias=True):
        """
        :param in_features: 输入特征
        :param out_features: 输出特征
        :param bias: 偏置
        """
        super(GraphConv, self).__init__()
        # self.GCN = np.random.normal(0,1,size=(in_features,out_features))
        self.in_features = in_features
        self.out_features = out_features
        # Parameter用于将参数自动加入到参数列表
        self.weight = Parameter(torch.FloatTensor(in_features, out_features))
        # torch.nn.init.normal(self.weight)
        if bias:
            self.bias = Parameter(torch.FloatTensor(out_features))
        else:
            self.register_parameter('bias', None)  # 为模型添加参数
        self.reset_parameters()
    def reset_parameters(self):
        stdv = 1. / math.sqrt(self.weight.size(1))
        self.weight.data.uniform_(-stdv, stdv)
        if self.bias is not None:
            self.bias.data.uniform_(-stdv, stdv)
    def forward(self, adj):
        # support = torch.mm(input, self.weight)
        # 最新spmm函数是在torch.sparse模块下，但是不能用
        # 使用稀疏矩阵乘法，
        output = torch.spmm(adj, self.weight)
        if self.bias is not None:
            return output + self.bias
        else:
            return output
    def __repr__(self):
        return self.__class__.__name__ + ' (' \
               + str(self.in_features) + ' -> ' \
               + str(self.out_features) + ')'




if __name__ == '__main__':
    inputs = torch.FloatTensor([[1, 0], [2, 1], [3, 2], [4, 3], [5, 4], [6,5]])
    adjs = torch.FloatTensor([
        [0, 1, 0, 0, 1, 0],
        [1, 0, 1, 0, 1, 0],
        [0, 1, 0, 1, 0, 0],
        [0, 0, 1, 0, 1, 1],
        [1, 1, 0, 1, 0, 0],
        [0, 0, 0, 1, 0, 0]
    ])
    g_conv = GraphConv(2, 3)
    outputs1 = F.relu(g_conv.forward(inputs, adjs))
    outputs2 = F.softmax(F.relu(g_conv.forward(inputs, adjs)))
    print(outputs1)
    print(outputs2)