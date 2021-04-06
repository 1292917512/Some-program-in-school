import codecs
import numpy as np

#构建一个邻接矩阵图
class Graph_Matrix:
    """
    Adjacency Matrix
    """
    def __init__(self, vertices=[], matrix=[]):
        """
        :param vertices:a dict with vertex id and index of matrix , such as {vertex:index}
        :param matrix: a matrix
        """
        self.matrix = matrix
        self.edges_dict = {}  # {(tail, head):weight}
        self.edges_array = []  # (tail, head, weight)
        self.vertices = vertices
        self.num_edges = 0

        # if provide adjacency matrix then create the edges list
        if len(matrix) > 0:
            if len(vertices) != len(matrix):
                raise IndexError
            self.edges = self.getAllEdges()
            self.num_edges = len(self.edges)

        # if do not provide a adjacency matrix, but provide the vertices list, build a matrix with 0
        elif len(vertices) > 0:
            self.matrix = [[0 for col in range(len(vertices))] for row in range(len(vertices))]
        self.num_vertices = len(self.matrix)

    def isOutRange(self, x):
        try:
            if x >= self.num_vertices or x <= 0:
                raise IndexError
        except IndexError:
            print("节点下标出界")

    def isEmpty(self):
        if self.num_vertices == 0:
            self.num_vertices = len(self.matrix)
        return self.num_vertices == 0

    def add_vertex(self, key):
        if key not in self.vertices:
            self.vertices[key] = len(self.vertices) + 1

        # add a vertex mean add a row and a column
        # add a column for every row
        for i in range(self.getVerticesNumbers()):
            self.matrix[i].append(0)

        self.num_vertices += 1

        nRow = [0] * self.num_verticesc

        self.matrix.append(nRow)

    def getVertex(self, key):
        pass

    def add_edges_from_list(self, edges_list):  # edges_list : [(tail, head, weight),()]
        for i in range(len(edges_list)):
            self.add_edge(edges_list[i][0], edges_list[i][1], edges_list[i][2], )

    def add_edge(self, tail, head, cost=0):
        # if self.vertices.index(tail) >= 0:
        #   self.addVertex(tail)
        if tail not in self.vertices:
            self.add_vertex(tail)
        # if self.vertices.index(head) >= 0:
        #   self.addVertex(head)
        if head not in self.vertices:
            self.add_vertex(head)

        # for directory matrix
        self.matrix[self.vertices.index(tail)][self.vertices.index(head)] = cost
        # for non-directory matrix
        # self.matrix[self.vertices.index(fromV)][self.vertices.index(toV)] = \
        #   self.matrix[self.vertices.index(toV)][self.vertices.index(fromV)] = cost

        self.edges_dict[(tail, head)] = cost
        self.edges_array.append((tail, head, cost))
        self.num_edges = len(self.edges_dict)

    def getEdges(self, V):
        pass

    def getVerticesNumbers(self):
        if self.num_vertices == 0:
            self.num_vertices = len(self.matrix)
        return self.num_vertices

    def getAllVertices(self):
        return self.vertices

    def getAllEdges(self):
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix)):
                if 0 < self.matrix[i][j] < float('inf'):
                    self.edges_dict[self.vertices[i], self.vertices[j]] = self.matrix[i][j]
                    self.edges_array.append([self.vertices[i], self.vertices[j], self.matrix[i][j]])

        return self.edges_array

    def __repr__(self):
        return str(''.join(str(i) for i in self.matrix))

    def to_do_vertex(self, i):
        print('vertex: %s' % (self.vertices[i]))

    def to_do_edge(self, w, k):
        print('edge tail: %s, edge head: %s, weight: %s' % (self.vertices[w], self.vertices[k], str(self.matrix[w][k])))
# matrix = [[0 for i in range(m)] for j in range(n)]


dic = {}    #保存候选
list2 = []  #保存候选为空情况
with codecs.open('aida_testA.csv','r','gbk','ignore') as f:
    for line in f:
        list = []  #创建字典对应候选的链表
        s=line.split("\t")  #以一个制表位分割一行
        i=6    #第1个候选的位置
        if(s[0] != "947testa"):   #控制第一篇
            break
        while(s[i]):
            s1 = s[i].split(",")
            if (s1[0] == 'EMPTYCAND'): #候选为空情况
                list2.append(s[2])   #储存候选为空的词
                break
            if(s[i]=="GT:"):  #候选对象结束标志
                break
            list.append((s1[2],s1[1])) #往链表里添加候选
            i=i+1
        dic[s[2]] = list #向大字典对因实体添加候选的链表



vertices = []  #顶点
matrix = []   #邻接矩阵
for key in dic:
    hx=dic[key]
    for evhx in hx:
        vertices.append((key,evhx))       #创建邻接矩阵（转化为对应） (对象，（候选，流行度）)

GM=Graph_Matrix(vertices,matrix)  #初始化并生成邻接矩阵




#将生成的邻接矩阵赋值
for V in GM.vertices:
    try:
        path = 'E:\wikinew\\'
        xxoo = path + V[1][0]+'.txt'   #找到对应候选对象的文件，文件中包含处理过的链接对象
        with open(xxoo, 'r') as f:
            for line in f:
                line = line.replace('\n','')
                for v in GM.vertices:
                    if (V[0] != v[0]):
                        if(line==v[1][0]):
                            GM.add_edge(V,v,1)  #将对应的值写入到矩阵当中
    except OSError as reason:
        pass
        # print('出错啦！' + str(reason))
    finally:
        f.close()


#pagerank
for i in range(GM.num_vertices):
    num = 0
    for j in range(GM.num_vertices):
       if(GM.matrix[j][i]==1):
           num=num+1
    for k in range(GM.num_vertices):
       if(GM.matrix[k][i]==1):
           GM.matrix[k][i]=1/num

dig = 1/GM.num_vertices
Matrixvertices = [dig]*GM.num_vertices
for i in range(len(Matrixvertices)):
    Matrixvertices[i]=float(vertices[i][1][1])

a = np.asarray(GM.matrix)
b = np.asarray(Matrixvertices)
n =100
while(n):
    c1=np.dot(a,b)
    b = c1
    n=n-1


dictionary = dict(zip(GM.vertices, c1))
for Tempdic in dictionary:
    break
max =0
maxdic = {}
ls = {}
for dickey in dictionary:
    if(Tempdic[0] == dickey[0]):
        if(dictionary[dickey]>max):
            max = dictionary[dickey]
            maxdic = dickey
    else:
        ls[maxdic]=max
        Tempdic = dickey
        max = dictionary[dickey]

file = open('tastAjieguo.txt', 'w',newline='')
for key in ls:
    file.write(str(key[0])+'='+str(key[1][0])+'\t')# 写入内容信息
file.close()


