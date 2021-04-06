import codecs
import os
#from numba import jit

def txt(name, l):  # 定义函数名
    namet = name
    namet=namet.replace(' ','')
    if (namet.isalpha()):
        b = os.getcwd()[:-4] + 'new\\'
        if not os.path.exists(b):  # 判断当前路径是否存在，没有则创建new文件夹
            os.makedirs(b)
        xxoo = b + name + '.txt'  # 在当前py文件所在路径下的new文件中创建txt
        file = open(xxoo, 'w',newline='')
        for s in l:
                file.write(s)  # 写入内容信息
        file.close()
   # print('ok')
dic = {}    #保存候选
list2 = []  #保存候选为空情况
with codecs.open('D:\\python_Object\\nlptest\\data\\test\\aida_testA.csv','r','gbk','ignore') as f:
    for line in f:
        list = []  #创建字典对应候选的链表
        s=line.split("\t")  #以一个制表位分割一行
        i=6    #第1个候选的位置
        if(s[0] != "947testa"):   #控制第一篇
            break
        while(s[i]):
            s1 = s[i].split(",")
            if (s1[0] == 'EMPTYCAND'): #候选为空情况
                print(s1[0])
                list2.append(s[2])   #储存候选为空的词
                break
            if(s[i]=="GT:"):  #候选对象结束标志
                break
            list.append(s1[2]) #往链表里添加候选
            i=i+1
        dic[s[2]] = list #向大字典对因实体添加候选的链表


l = []
l2 = []
t = "t"
t2 = "t2"
with codecs.open('F:\\pageLinkGraph.txt', 'r', 'gbk', 'ignore') as f:
    for line in f:
        linesplit = line.split("\t")
        for key in dic:
            cl = dic[key]
            for cd in cl:
                if(linesplit[2]==cd):
                    # print(linesplit[2])
                    if(t != linesplit[2]):
                        txt(t,l2)
                        l2.clear()
                        l2.append(linesplit[3])
                    else:
                        if(t2!=linesplit[3]):
                            t2 = linesplit[3]
                            l2.append(linesplit[3])
                    t = linesplit[2]

    #     flag = 0
    #     s=line.split("\t")
    #     if(t!=s[2]):
    #         i = i+1
    #         for key in dic:
    #             le = dic[key]
    #             for ss in le:
    #                 if(ss==t):
    #                     flag =1
    #         if(flag == 1):
    #             txt(t,l2)
    #             l2.clear()
    #             l.append(s[2])
    #             l2.append(s[3])
    #     else:
    #         l2.append(s[3])
    # t = s[2]