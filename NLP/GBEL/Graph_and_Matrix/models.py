import torch.nn as nn
import torch.nn.functional as F
from Graph_and_Matrix.layers import GraphConvolution



"""目前最优"""
class GCN(nn.Module):
    def __init__(self, nfeat, nhid,nhid2, nclass, dropout):
        super(GCN, self).__init__()
        self.l1_1 = nn.Linear(300, 1500)
        # self.l1 = nn.Linear(30,1500)
        self.gc1 = GraphConvolution(nfeat, nhid)
        self.gc2 = GraphConvolution(nhid, nclass)
        self.gc3 = GraphConvolution(nhid2,nclass)
        # self.l2 = nn.Linear(1500,30)
        # self.l3 = nn.Linear(30,30)
        self.l4 = nn.Linear(30,2)
        self.dropout = dropout



    def forward(self, x, adj,adj2):
        x = self.l1_1(x)
        # x = self.l1(x.t())
        x = F.relu(self.gc1(x.t(), adj))
        x = F.dropout(x, self.dropout, training=self.training)
        x = self.gc2(x,adj)
        x = self.gc3(x,adj2)
        # x = self.l2(x.t())
        # x = self.l3(x)
        x = self.l4(x)
        return F.log_softmax(x,dim=1)

class GCN2(nn.Module):
    def __init__(self, nfeat, nhid,nhid2, nclass,nclass2, dropout):
        super(GCN2, self).__init__()
        self.l1_1 = nn.Linear(300, 1500)
        # self.l1 = nn.Linear(30,1500)
        self.gc1 = GraphConvolution(nfeat, nhid)
        self.gc2 = GraphConvolution(nhid, nclass)
        self.gc3 = GraphConvolution(nhid2,nclass2)
        # self.l2 = nn.Linear(1500,30)
        # self.l3 = nn.Linear(30,30)
        self.l4 = nn.Linear(30,30)
        self.dropout = dropout



    def forward(self, x, adj,adj2):
        x = self.l1_1(x)
        # x = self.l1(x.t())
        x = F.relu(self.gc1(x.t(), adj))
        x = F.dropout(x, self.dropout, training=self.training)
        x = self.gc2(x,adj)
        x = self.gc3(x,adj2)
        # x = self.l2(x.t())
        # x = self.l3(x)
        x = self.l4(x.t())
        return F.log_softmax(x,dim=1)