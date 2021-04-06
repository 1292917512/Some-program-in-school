import re
import os
import numpy as np
from Graph_and_Matrix.Adjacency_matrix import Graph_Matrix

#--------------------------文件操作函数-----------------------------------------------------------------------------------


#-----------------------------------------------------------------------------------------------------------------------



#--------------------------图操作函数-------------------------------------------------------------------------------------
def createGM_loss(trainlist):
    MatrixGraph = []
    a =[]
    for i in range(len(trainlist)):
        for art in trainlist[i]:
            Candidatedic = trainlist[i][art]
            vertices = [] #顶点
            matrix = []   #邻接矩阵
            for key in Candidatedic:
                hx=Candidatedic[key]
                for evhx in hx[0]:
                    vertices.append((key,evhx))
                a.append(hx[1][0])
            MatrixGraph.append(Graph_Matrix(art, vertices, matrix))
            #创建邻接矩阵（转化为对应） (对象，（候选，流行度）)hx[1][0]
            # txt2(MG.artname, MG.matrix)
    print("图构建完成")
    return MatrixGraph,a

#数据矩阵读入供主函数使用
class GraphDataset():
    def __init__(self):
        self.Graph_dir ="D:\\python_Object\\nlptest\\Generate_Graphfile\\"
        self.filels = []
        for root,dirs,file in os.walk(self.Graph_dir):
            self.filels=file
    def get_filematrix(self, dataname):
        return np.loadtxt(self.Graph_dir+dataname).astype(np.float32)

#供Generate_graph.py使用
def get_relationset(name):                 #通过对应文章名字  获取文章位置
    relationls = []
    name = re.findall(r"\d+\.?\d*", name)[0]
    name = name.replace(' ', '')
    dir = 'E:\\python_Object\\GCN_Entity_Linking\\Generate_data\\'
    fp = dir + name + '.txt'
    try:
        with open(fp, 'r') as f:
            for line in f:
                linesplit = line.split('\t')
                relationls.append((linesplit[2], linesplit[3].replace('\n', '')))
    except OSError as reason:
        pass
        # print('出错啦！' + str(reason))
    finally:
        f.close()
    return set(relationls)


def txt(name, matrix):  #用来生成对应的矩阵
    name = name.replace(' ', '')
    b = os.getcwd()[:-5] + 'Graphfile_old\\'
    if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
        os.makedirs(b)
    namepath = b+ name
    np.savetxt(namepath, matrix)

def txt2(name, matrix):  #用来生成对应的矩阵
    name = name.replace(' ', '')
    b = os.getcwd()[:-5] + 'Graphfile_loss\\'
    if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
        os.makedirs(b)
    namepath = b+ name
    np.savetxt(namepath, matrix)

#打印平均候选数量
def find_hxavg(train):
    i,n = 0,0
    for dir in train[0]:
        i += len(dir)
        n += 1
    print(i/n)


def createGM(trainlist):
    MatrixGraph = []
    for i in range(len(trainlist)):
        for art in trainlist[i]:
            Candidatedic = trainlist[i][art]
            vertices = [] #顶点
            matrix = []   #邻接矩阵
            for key in Candidatedic:
                hx=Candidatedic[key]
                for evhx in hx[0]:
                    vertices.append((key,evhx))
                    # a = hx[0].index(hx[1])
                    # print(a)
            MatrixGraph.append(Graph_Matrix(art,vertices,matrix))  #创建邻接矩阵（转化为对应） (对象，（候选，流行度）)
    print("图构建完成")
    return MatrixGraph



#-----------------------------------------------------------------------------------------------------------------------



#-----------------------------------------------------------------------------------------------------------------------
#根据对应的实体候选选生成对应的求loss图,固定大小
def createGM_loss(MGlist,hx_num):
    print("正在生成求LOSS数据邻接图")
    i = 0
    for MG in MGlist:
        MG_hx =len(MG.vertices)
        if(hx_num>MG_hx):
            for V in MG.vertices:
                pass

#创建非固定大小的图
# def Generate_Graph(MGlist):
#     print("正在创建图")
#     i=0
#     for MG in MGlist:
#         relation = get_relationset(MG.artname)
#         for V in MG.vertices:
#             for v in MG.vertices:
#                 if(V[0]!=v[0]):
#                     if((V[1][0],v[1][0]) in relation):
#                         MG.add_edge(V,v,1)
#         # txt(MG.artname,MG.matrix)       #将生成的邻接矩阵保存
#         # i = i+1
#         # if(i%50==0):
#         #     print("已创建写入"+str(i)+"张图")
#     print("图创建写入完毕")


if __name__ == '__main__':

    wikiGraph = 'D:\\python_Object\\nlptest\\data\\wikiGraph\\pageLinkGraph.txt'
    MGls = createGM()
    # Generate_Graph(MGls)
