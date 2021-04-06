import math
import numpy as np
import torch

from torch.nn.parameter import Parameter
from torch.nn.modules.module import Module


def processAdj(adj, self_loop=True,**kwargs):
    """
    :param adj: 邻接矩阵，type：np.array(float)
    :param self_loop: boolean
    :return: adj
    """
    adj = adj.astype(float)
    opt = {}
    opt['normal'] = kwargs.get('normal', False)
    opt['sym_normal'] = kwargs.get('sym_normal', False)
    if not opt['normal'] and not opt['sym_normal']:
        return adj

    if self_loop:
        adj = adj + np.eye(adj.shape[0])

    if opt['sym_normal']:  # 对称归一化
        degree = np.diag(np.sum(adj, axis=1)) ** -0.5
        return np.matmul(np.matmul(degree, adj), degree)
    if opt['normal']:  # 归一化
        degree = np.diag(np.sum(adj, axis=1)) ** -1
        return np.matmul(degree, adj)

class GraphConvolution(Module):
    """
    Simple GCN layer, similar to https://arxiv.org/abs/1609.02907
    """

    def __init__(self, in_features, out_features, bias=True):
        super(GraphConvolution, self).__init__()
        self.in_features = in_features
        self.out_features = out_features
        self.weight = Parameter(torch.FloatTensor(in_features, out_features))
        if bias:
            self.bias = Parameter(torch.FloatTensor(out_features))
        else:
            self.register_parameter('bias', None)
        self.reset_parameters()

    def reset_parameters(self):
        stdv = 1. / math.sqrt(self.weight.size(1))
        self.weight.data.uniform_(-stdv, stdv)
        if self.bias is not None:
            self.bias.data.uniform_(-stdv, stdv)

    def forward(self, input, adj):
        support = torch.mm(input, self.weight)
        output = torch.spmm(adj, support)
        if self.bias is not None:
            return output + self.bias
        else:
            return output

    def __repr__(self):
        return self.__class__.__name__ + ' (' \
               + str(self.in_features) + ' -> ' \
               + str(self.out_features) + ')'
