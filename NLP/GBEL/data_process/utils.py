#数据矩阵读入供主函数使用
import os
import numpy as np
import gensim



class GraphDataset():
    def __init__(self,dir):
        self.Graph_dir =dir
        self.filels = []
        for root,dirs,file in os.walk(self.Graph_dir):
            self.filels=file
    def get_filematrix(self, dataname):
        return np.loadtxt(self.Graph_dir+'\\'+dataname).astype(np.float32)