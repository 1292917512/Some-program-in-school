import re
import os
import numpy as np
import gensim
import codecs
import copy
import _pickle as pickle
from Graph_and_Matrix.Adjacency_matrix import Graph_Matrix
from data_process.data_process_function import Get_data
MAX_HX = 30
MAX_WORD = 50
ELEN = MAX_HX*MAX_WORD
Empty = "NULL"
import torch

#--------------------------文件操作函数-----------------------------------------------------------------------------------
def txt(name, matrix):  #用来生成对应的矩阵
    name = name.replace(' ', '')
    b = os.getcwd()[:-7] + 'Graphfile_tastA\\'
    if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
        os.makedirs(b)
    namepath = b+ name
    np.savetxt(namepath, matrix)

def input_tr(trainlist):
    f = open("../data/hx.txt",'w+')
    for key in trainlist[0]:
        f.write(key+'\t')
        for hx in trainlist[0][key]:
            f.write(hx+'\t')
        f.write('\n')
    print("写入完成")
    f.close()


def txt_loss(name, matrix):  # 用来生成对应的矩阵
    name = name.replace(' ', '')
    b = os.getcwd()[:-7] + 'Graphfile_loss_testA\\'
    if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
        os.makedirs(b)
    namepath = b + name
    np.savetxt(namepath, matrix)

def get_relationset(name):                 #通过对应文章名字  获取文章位置
    relationdic = {}
    # name = re.findall(r"\d+\.?\d*", name)[0]
    name = name.replace(' ', '')
    dir = 'E:\\python_Object\\GCN_Entity_Linking\\data_rel_ace2004\\'
    fp = dir + name + '.txt'
    try:
        with open(fp, 'r') as f:
            for line in f:
                linesplit = line.split('\t')
                relation = (linesplit[2], linesplit[3].replace('\n', ''))
                relationdic[relation] = 1
    except OSError as reason:
        pass
        print('出错啦！' + str(reason))
    finally:
        f.close()
    return relationdic


def get_relationset_2(name,dir):                 #通过对应文章名字  获取文章位置
    relationls = []
    value = []
    name = re.findall(r"\d+\.?\d*", name)[0]
    name = name.replace(' ', '')
    fp = dir + name
    try:
        with open(fp, 'r',encoding='utf-8') as f:
            for line in f:
                linesplit = line.split('\t')
                relationls.append((linesplit[1], linesplit[2].replace('\n', '')))
                value.append(float(linesplit[3].replace('\n','')))
    except OSError as reason:
        pass
        # print('出错啦！' + str(reason))
    finally:
        f.close()
    return relationls,value





def get_Similarity(DIR_dx,DIR_Similarity):
    ls1 = []
    ls2 = []
    with codecs.open(DIR_dx, 'r', 'gbk', 'ignore') as f:
        for line in f:
            s = line.split("<--->")
            ls1.append((s[0],s[2]))
    with codecs.open(DIR_Similarity, 'r', 'gbk', 'ignore') as f:
        for line in f:
            print(line)
            line = line.replace("\n","").replace("[","").replace("]","")
            print(line)
            # line = line.split(" ")
            # if(len(line)==3):
            #     line = line[2]
            # else:
            #     line = line[1]
            print(line)
            print("----------")
            ls2.append(float(line))
    return dict(zip(ls1,ls2))


#-----------------------------------------------------------------------------------------------------------------------
def get_keys(d, value):
    return [k for k,v in d.items() if v == value]

#--------------------------图操作函数-------------------------------------------------------------------------------------







# trainlist
# def createGM_loss():
#     return np.zeros((ELEN,ELEN))


# def createGM_loss(trainlist):
#     MatrixGraph = []
#     a =[]
#     for i in range(len(trainlist)):
#         for art in trainlist[i]:
#             Wordlist = trainlist[i][art]
#             if(len(trainlist[i][art])>MAX_WORD):
#                 continue
#             vertices = []       #顶点
#             matrix = []         #邻接矩阵
#             index =0
#             for index in range(len(Wordlist)):
#                 CDlist = Wordlist[index]
#             if(index<MAX_HX):
#                 for _ in range(index,MAX_HX):
#                     pass #插入文章操作

def createGM(trainlist):
    target = []
    targetls=[]
    MatrixGraph = []
    a = []
    # for i in range(len(trainlist)-1):
    for artnum,art in enumerate(trainlist):
        # n = re.findall(r"\d+\.?\d*", art)[0]
        # n = int(n)
        # if(n<1183):
        #     continue
        Wordlist = trainlist[art]
        Wordlen = len(Wordlist)
        if (Wordlen> MAX_WORD):
            continue
        vertices = []  # 顶点
        matrix = []  # 邻接矩阵
        index = 0
        for num,Word in enumerate(Wordlist):
            CDlist = Wordlist[Word]
            TGindex = (int(CDlist[1][0]) - 1)
            CDlen = len(CDlist[0])
            if(TGindex<CDlen and CDlen!=0 and TGindex<30 and TGindex!=-2):
                TG = CDlist[0][TGindex]
            else:
                TG = 'NULL'
            targetls.append((Word, TG))
            if(CDlen<=MAX_HX):
                for hxindex in CDlist[0]:
                    vertices.append((Word,hxindex)) #保留流行度
                    # vertices.append((Word, hxindex[0]))
                if (CDlen <= MAX_HX):
                    for _ in range(CDlen,MAX_HX):
                        vertices.append((Word,"NULL"))
            if(CDlen>MAX_HX):
                for i in range(MAX_HX):
                    vertices.append((Word,CDlist[0][i]))
            # if(TG<=MAX_HX):
                # targetls.append(TG + num * MAX_HX)
        if(Wordlen<=MAX_WORD):
            for i in range(Wordlen,MAX_WORD):
                for _ in range(MAX_HX):
                    vertices.append(("NULL","NULL"))
                targetls.append('NULL')
        target.append(copy.deepcopy(targetls))
        targetls.clear()
        # 创建邻接矩阵（转化为对应） (对象，（候选，流行度）)hx[1][0]
        MatrixGraph.append(Graph_Matrix(art, vertices, matrix))
    return MatrixGraph,target

# def createGM(trainlist):
#     target = []
#     targetls=[]
#     MatrixGraph = []
#     a = []
#     # for i in range(len(trainlist)-1):
#     for artnum,art in enumerate(trainlist[0]):
#         n = re.findall(r"\d+\.?\d*", art)[0]
#         n = int(n)
#         if(n<1000 or n>1009):
#             continue
#         Wordlist = trainlist[0][art]
#         Wordlen = len(Wordlist)
#         if (Wordlen> MAX_WORD):
#             continue
#         vertices = []  # 顶点
#         matrix = []  # 邻接矩阵
#         index = 0
#         for num,Word in enumerate(Wordlist):
#             CDlist = Wordlist[Word]
#             TGindex = (int(CDlist[1][0]) - 1)
#             CDlen = len(CDlist[0])
#             if(TGindex<CDlen and CDlen!=0 and TGindex<30):
#                 TG = CDlist[0][TGindex]
#             else:
#                 TG = 'NULL'
#             targetls.append((Word, TG))
#             ls = []
#             if(CDlen<=MAX_HX):
#                 for hxindex in CDlist[0]:
#                     ls.append((Word,hxindex)) #保留流行度
#                     # vertices.append((Word, hxindex[0]))
#                 for v in set(ls):
#                     vertices.append(v)
#                 vlen = len(set(ls))
#                 if (CDlen <= MAX_HX):
#                     for _ in range(vlen,MAX_HX):
#                         vertices.append((Word,"NULL"))
#             if(CDlen>MAX_HX):
#                 for i in range(MAX_HX):
#                     ls.append((Word,CDlist[0][i]))
#                 ls = list(set(ls))
#                 vlen = len(ls)
#                 if (vlen <= MAX_HX):
#                     for _ in range(vlen,MAX_HX):
#                         ls.append((Word,"NULL"))
#                 vertices = ls + vertices
#             # if(TG<=MAX_HX):
#                 # targetls.append(TG + num * MAX_HX)
#         if(Wordlen<=MAX_WORD):
#             for i in range(Wordlen,MAX_WORD):
#                 for _ in range(MAX_HX):
#                     vertices.append(("NULL","NULL"))
#                 targetls.append('NULL')
#         target.append(copy.deepcopy(targetls))
#         targetls.clear()
#         # 创建邻接矩阵（转化为对应） (对象，（候选，流行度）)hx[1][0]
#         MatrixGraph.append(Graph_Matrix(art, vertices, matrix))
#     return MatrixGraph,target

def Generate_Graph_loss_old(MGlist,target):
    print("正在创建标识图")
    count = 0
    for num,targetlist  in enumerate(target):
        MG = MGlist[num]
        for i in targetlist:
            for j in targetlist:
                MG.add_edge(MG.vertices[i], MG.vertices[j], 1)
        txt_loss(MG.artname, MG.matrix)  # 将生成的邻接矩阵保存
        count = count + 1
        if (count % 50 == 0):
            print("已创建写入" + str(count) + "张图")
    return MGlist

# def Generate_Graph_loss(MGlist,target):
#     print("正在创建标识图")
#     count = 0
#     for num,targetlist  in enumerate(target):
#         tag = np.zeros((1,ELEN))
#         MG = MGlist[num]
#         for i in targetlist:
#             if(i>=0):
#                 tag[0][i] =1
#         txt_loss(MG.artname,tag)  # 将生成的邻接矩阵保存
#         count = count + 1
#         if (count % 50 == 0):
#             print("已创建写入" + str(count) + "张图")
#     return MGlist

def Generate_Graph_loss(MGlist,target,diraim):
    print("正在创建标识图")
    for i,MG in enumerate(MGlist):
        aim = np.zeros(shape=(1,len(MG.vertices)))
        for tag in target[i]:
            if(tag!='NULL'):
                try:
                    mk = MG.vertices.index(tag)
                    aim[0][mk] = 1
                except:
                    print(MG.artname)
                    print(tag)
        dir = diraim+MG.artname
        np.savetxt(dir,aim)



def Generate_Graph(MGlist):
    print("正在创建图")
    i = 0
    for MG in MGlist:
        relationdic = get_relationset(MG.artname)
        for V in MG.vertices:
            if(V[1]=='NULL'):
                continue
            for v in MG.vertices:
                if (v[1] == 'NULL'):
                    continue
                if (V[0] != v[0]):  #不为同一个指称
                    try:
                        i = relationdic[(V[1],v[1])]
                        MG.add_edge(V,v,i)
                    except:
                        pass
        # filename = dir +MG.artname
        dir = 'E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_wiki\\wiki_ace2004\\'+MG.artname
        np.savetxt(dir,MG.matrix)
        i = i + 1
        if (i % 50 == 0):
            print("已创建写入" + str(i) + "张图")
    return MGlist
    # print("图创建写入完毕")


def Generate_Graph_2(MGlist,dir1,dir2):
    print("正在创建图")
    i = 0
    for MG in MGlist:
        relation,value = get_relationset_2(MG.artname,dir1)
        for V in MG.vertices:
            for v in MG.vertices:
                if (V[0] != v[0]):  #不为同一个指称
                    try:
                        i = relation.index((V[1], v[1]))
                        MG.add_edge(V,v,value[i])
                    except:
                        pass
        # txt(MG.artname, MG.matrix)  # 将生成的邻接矩阵保存
        dir = dir2+MG.artname
        np.savetxt(dir,MG.matrix)
        i = i + 1
        if (i % 50 == 0):
            print("已创建写入" + str(i) + "张图")
    return MGlist
    # print("图创建写入完毕")


def get_relationset_3(name):                 #通过对应文章名字  获取文章位置
    # relationls = []
    # value = []
    dic = {}
    # name = re.findall(r"\d+\.?\d*", name)[0]
    name = name.replace(' ', '')
    # name = name.replace(".htm","")
    name = name +"_candidate_cosine_similarity.txt"
    dir = 'E:\\python_Object\\GCN_Entity_Linking\\data\\gm_sm_data\\simres-clueweb\\'
    fp = dir + name
    try:
        with open(fp, 'r',encoding='utf-8') as f:
            for line in f:
                linesplit = line.split('\t')
                relation = (linesplit[0], linesplit[1].replace('\n', ''))
                value = float(linesplit[2].replace('\n','').replace('[','').replace(']',''))
                dic[relation] = value
                # relationls.append((linesplit[0], linesplit[1].replace('\n', '')))
                # value.append(float(linesplit[2].replace('\n','').replace('[','').replace(']','')))
    except OSError as reason:
        print('出错啦！' + str(reason))
        return 0
    f.close()
    # return relationls,value
    return dic

def Generate_Graph_3(MGlist):
    print("正在创建图")
    for MG in MGlist:
        print("加载{}关系中".format(MG.artname))
        dic = get_relationset_3(MG.artname)
        if(dic==0):
            continue
        print("构建邻接矩阵ing")
        for V in MG.vertices:
            if(V[1]=='NULL'):
                continue
            for v in MG.vertices:
                if (v[1] == 'NULL'):
                    continue
                if (V[0] != v[0]):  #不为同一个指称
                    try:
                        i = dic[(V[1],v[1])]
                        # i = relation.index((V[1], v[1]))
                        MG.add_edge(V,v,i)
                    except:
                        pass
        # txt(MG.artname, MG.matrix)  # 将生成的邻接矩阵保存
        print("矩阵构建完成")
        dir = 'E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_sm\\wned-clueweb\\'+MG.artname
        np.savetxt(dir,MG.matrix)
        print("已创建写入图" + MG.artname)
    return MGlist



def w_f2(GM,dirname):
    for art in GM:
        dir = "E:\\python_Object\\GCN_Entity_Linking\\data\\featuredata\\pkl\\gcn" + dirname +art.artname+'.pkl'
        f = open(dir,'rb')
        pk = pickle.load(f)
        ls = np.zeros((1, 768))
        t = np.zeros((1,768))
        for v in art.vertices:
            if(v[1]=='NULL'):
                ls = np.vstack((ls,t))
            else:
                try:
                    ls = np.vstack((ls,pk[v[1]].to('cpu').numpy()))
                except:
                    print(v[1])
                    ls = np.vstack((ls,t))
        # fm = model[ls]
        fm = np.delete(ls,0, axis = 0)
        name = art.artname.replace(' ', '')
        np.savetxt("E:\\python_Object\\GCN_Entity_Linking\\data\\feature2\\"+name,fm)

def w_f(GM):
    Goolge = "F:\\学习工作\\shara\\DGCN_EL\\data\\GoogleNews-vectors-negative300.bin"
    model = gensim.models.KeyedVectors.load_word2vec_format(Goolge, binary=True)
    for art in GM:
        ls = np.zeros((1, 300))
        t = np.zeros((1,300))
        for v in art.vertices:
            if(v[1]=='NULL'):
                ls = np.vstack((ls,model['NULL']))
            else:
                try:
                    aim = v[1].split(" ")[0]
                    ls = np.vstack((ls,model[aim]))
                except:
                    print(v[1])
                    ls=  np.vstack((ls,model['NULL']))
        # fm = model[ls]
        fm = np.delete(ls,0, axis = 0)
        name = art.artname.replace(' ', '')
        np.savetxt("E:\\python_Object\\GCN_Entity_Linking\\data\\feature\\"+name,fm)


def get_Similarity_Graph(MGlist,dic,dir):
    print("正在创建标识图")
    for MG in MGlist:
        aim = np.zeros(shape=(1,len(MG.vertices)))
        for i,v in enumerate(MG.vertices):
            if(v[1]!='NULL'):
                try:
                    aim[0][i]=dic[v]
                except:
                    print(v)
        dir2 = dir+(MG.artname.replace(" ",""))
        np.savetxt(dir2,aim)


def txt_wiki(name, l):  # 定义函数名
    # name = re.findall(r"\d+\.?\d*", name)
    print("开始写第"+name+"篇文章")
    name = name.replace(' ', '')
    b = "E:\\python_Object\\GCN_Entity_Linking\\data_rel_ace2004\\"
    if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
        os.makedirs(b)
    name = b+ name+ ".txt"
    file = open(name, 'w+',newline='')
    for s in l:
        file.write(s)  # 写入内容信息
    file.close()
    print("完成")


def wikiGrahpdel(GM):
    wikiGraph = 'E:\\python_Object\\pageLinkGraph.txt'
    ls = []
    hxlist = []
    for art in GM:
        txt_wiki(art.artname, ls)
        for hx in art.vertices:
            if(hx[1]!='NULL'):
                hxlist.append(hx[1])
        hxset = set(hxlist)
        print(art.artname + "loading")
        with codecs.open(wikiGraph, 'r', 'gbk', 'ignore') as f:  # 打开准备好的wiki关系图,将每一篇文档里所对应的点的联系全部写出来
            for line in f:
                linesplit = line.split("\t")
                if (linesplit[2] in hxset):
                    ls.append(line)  # 将所有的对应有关系的行保存为一个列表
        txt_wiki(art.artname, ls)
        ls.clear()
        hxlist.clear()




def deldata(dir):
    dic = {}    #文件所有文章{文章编号:art{}}
    art = []   #保存一篇文章 格式{对象:候选集列表(list)(候选和流行度的元组),}
    list2 = []  #保存候选为空情况
    list = [] #创建字典对应候选的链表
    artnum = '0'
    file1 = open("E:\\python_Object\\GCN_Entity_Linking\\data\\deldata\\wned-wikipedia_Processed.csv", 'w+', newline='')
    # file1 = open("E:\\python_Object\\GCN_Entity_Linking\\data\\deldata\\wned-clueweb_Processed.csv", 'w+', newline='')
    with codecs.open(dir,'r','gbk','ignore') as f:
        for line in f:
            s=line.split("\t")  #以一个制表位分割一行
            # name = "E:\\python_Object\\GCN_Entity_Linking\\data\\deldata_clueweb\\"+s[0]
            name = "E:\\python_Object\\GCN_Entity_Linking\\data\\deldata_wikipedia\\" + s[0]
            file2 = open(name, 'a+', newline='')
            wz = s[3] + s[4]
            i=6    #第1个候选的位置
            if(s[0] != artnum):   #控制第一篇
                if(artnum!='0'):
                    # return art
                    dic[artnum]=copy.deepcopy(art)
                    art.clear()
                artnum = s[0]
            while(s[i]):
                s1 = s[i].split(",")
                if (s1[0] == 'EMPTYCAND'): #候选为空情况
                    list2.append(s[2])   #储存候选为空的词
                    break
                else:
                    if(s[i]=="GT:"):  #候选对象结束标志
                        t = (s[i + 1].split(","))
                        t = ','.join(t[3:])
                        t = t.replace("\n","")
                        break
                # list.append((s1[2],s1[1]))      #往链表里添加候选
                str = ','.join(s1[2:])
                fls=[s[0],s[2],wz,str,s1[1]]
                # flsstr = '<--->'.join(fls)
                # flsstr = flsstr+'\n'
                list.append(fls)
                i=i+1
            for num,flsdata in enumerate(list):
                if(num==30):
                    break;
                if(t == flsdata[3]):
                    flsdata.append('1')
                else:
                    flsdata.append('0')
                flsstr = '<--->'.join(flsdata)
                flsstr = flsstr+'\n'
                file1.write(flsstr)
                fls2 = [flsdata[0],flsdata[1],flsdata[3],flsdata[4],flsdata[5]]
                flsstr2 ='\t'.join(fls2)
                flsstr2 = flsstr2 + '\n'
                file2.write(flsstr2)
            list.clear()
            file2.close()
    file1.close()
    return  dic


def get_mbhx(GM):
    dir = "E:\\python_Object\\GCN_Entity_Linking\\data\\jg_unbert_wiki\\"
    dir2 = "E:\\python_Object\\GCN_Entity_Linking\\data\\jg_hx\\"
    filename2 = dir2+"testA_r_unbert.txt"
    f2 = open(filename2, 'w+')
    for GM_data in GM:
        filename = dir + GM_data.artname
        f = open(filename,'r')
        line = f.readline()
        lsnum = line.split(" ")[0:-1]
        name = re.findall(r"\d+\.?\d*", GM_data.artname)[0]
        f2.write('*'+name+'\n')
        for index,i in enumerate(lsnum):
            data = GM_data.vertices[int(i)+index*30]
            if(data[1]=="NULL"):
                continue
            str = data[0]+'='+data[1]+';'
            f2.write(str)
            f.close()
        f2.write('\n')
    f2.close()


def Result_rata():
    dir1 = "E:\\python_Object\\GCN_Entity_Linking\\data\\jg_hx\\testA-Result"
    dir2 = "E:\\python_Object\\GCN_Entity_Linking\\data\\jg_hx\\testA_r_unbert.txt"
    f1 = open(dir1,'r')
    f2 = open(dir2,'r')
    count =0
    num = 0
    while f1.readline()==f2.readline() :
        c1 = f1.readline()
        c2 = f2.readline()
        c1 = c1.split(';')
        c2 = c2.split(';')
        for hx in c1:
            if(hx == '\n'):
                continue
            num = num+1
            if(hx in set(c2)):
                count = count+1
            # if(hx not in set(c2)):
            #     print("标记")
    f1.close()
    f2.close()
    print(count/num)


def get_relation():                 #通过对应文章名字  获取文章位置
    relationdic = {}
    dir = 'E:\python_Object\GCN_Entity_Linking\wiki_graph.txt'
    try:
        with open(dir, 'r') as f:
            for line in f:
                linesplit = line.split('\t')
                relation = (linesplit[2], linesplit[3].replace('\n', ''))
                relationdic[relation] = 1
    except OSError as reason:
        pass
        print('出错啦！' + str(reason))
    finally:
        f.close()
    return relationdic


def get_Graph(MG):
    relationdic = get_relation()
    for V in MG.vertices:
        for v in MG.vertices:
            try:
                i = relationdic[(V,v)]
                MG.add_edge(V,v,i)
            except:
                pass
    # filename = dir +MG.artname
    dir = 'E:\\python_Object\\GCN_Entity_Linking\\'+MG.artname
    np.savetxt(dir,MG.matrix)





def writer_wiki(name, l):  # 定义函数名
    # name = re.findall(r"\d+\.?\d*", name)
    print("开始写第"+name+"篇文章")
    name = name.replace(' ', '')
    b = "E:\\python_Object\\GCN_Entity_Linking\\"
    name = b+ name+ ".txt"
    file = open(name, 'w+',newline='')
    for s in l:
        file.write(s)  # 写入内容信息
    file.close()
    print("完成")

def getwikiGrahp(list):
    wikiGraph = 'E:\\python_Object\\pageLinkGraph.txt'
    ls = []
    hxset = set(list)
    with codecs.open(wikiGraph, 'r', 'gbk', 'ignore') as f:  # 打开准备好的wiki关系图,将每一篇文档里所对应的点的联系全部写出来
        for line in f:
            linesplit = line.split("\t")
            if (linesplit[2] in hxset):
                ls.append(line)  # 将所有的对应有关系的行保存为一个列表
    writer_wiki('wiki_graph', ls)
    ls.clear()


if __name__ == '__main__':
    DIR = "E:\python_Object\GCN_Entity_Linking\data"  # 保存训练集和测试集的路径
    # DIR2 = "E:\python_Object\GCN_Entity_Linking\data\deldata\wned-clueweb.csv"
    # DIR3 ="E:\python_Object\GCN_Entity_Linking\data\deldata\wned-testb.csv"
    # dic = deldata(DIR3)
    # DIR_Graph = "D:\python_Object\GCN_Entity_Linking\Graph_data"  # 保存对应图数据的路径

    sm = ['Data-ace2004', 'Data-aquaint', 'Data-clueweb', 'Data-msnbc', 'Data-testB','Data-testA', 'Data-wikipedia','Data-aida']
    list = ['Singapore','Singapore Passports','London','London, California','South Korea','Koreans','Australia','Australia']
    DIR_sm_data = "E:\\python_Object\\GCN_Entity_Linking\\data\\Text_similarity\\sm\\"
    DIR_sm_result = "E:\\python_Object\\GCN_Entity_Linking\\data\\Text_similarity\\sm_result_bert\\"
    DIR_sm_aim = "E:\\python_Object\\GCN_Entity_Linking\\data\\sm_unbert\\"
    result = 'result_'
    # art = 'wiki_graph'
    # matrix = []
    trainlist,testlist = Get_data(DIR)
    GM,target= createGM(testlist[2])

    # diraim = "E:\\python_Object\\GCN_Entity_Linking\\data\\gm_loss\\"
    # GM = Graph_Matrix(art, list, matrix)
    # getwikiGrahp(GM.vertices)
    # get_mbhx(GM)
    # Result_rata()
    dd = DIR_sm_data + sm[0]
    dir ="E:\\python_Object\\GCN_Entity_Linking\\data\\Text_similarity\\sm_result_stm\\"
    dr = dir + 'lstm-ace2004.txt'   #result +sm[2] +'.txt'
    da = DIR_sm_aim
    dic = get_Similarity(dd,dr)
    get_Similarity_Graph(GM,dic,da)
    # input_tr(trainlist)
    # l = w_f2(GM,'clueweb\\')
    # l = w_f(GM)
    # wikiGrahpdel(GM)
    # MG = Generate_Graph_loss(GM,target,diraim)   #构建loss标识图
    # MG = Generate_Graph_3(GM)  #构建关系/图
    # MG =Generate_Graph(GM)
    # MG = get_Graph(GM)