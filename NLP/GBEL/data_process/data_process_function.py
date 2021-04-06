import os
import copy
import codecs
data_label = {"test": 0, "tain": 1}   #用于后面分训练集和测试集 2为wiki库数据目录

"""
文件读取函数，get_data负责读取对应的data_dair(数据目录)下的所有的训练集合测试集，并将其分类
"""
def get_data_dir(data_dir):
    data_info = list()
    for root,dirs,file in os.walk(data_dir):                            #获取目录文件夹和文件名字
        for sub_dir in dirs:
            data_names = os.listdir(os.path.join(root,sub_dir))              #将每个文件夹的名字写入
            # print(data_names)
            data_names = list(filter(lambda x:x.endswith('.csv'),data_names))         #提取出对应文件夹里.csv结尾的文件
            # print(data_names)
            # return data_name
            for i in range(len(data_names)):
                data_name = data_names[i]
                data_name = os.path.join(root, sub_dir, data_name)
                label = data_label[sub_dir]                           #sub_dir是对应文件夹名字  label表示训练集或测试集 0为测试，1为训练
                data_info.append((data_name, int(label)))               #将对应文件名和所在文件夹的表示写入列表
    return data_info
#-----------------------------------------------------------------------------------------------------------------------
"""
将所给路径的文章化为对应的词和候选集合
"""

def createCDD(datafile_path):
    dic = {}    #文件所有文章{文章编号:art{}}
    art = {}    #保存一篇文章 格式{对象:候选集列表(list)(候选和流行度的元组),}
    list2 = []  #保存候选为空情况
    artnum = '0'
    with codecs.open(datafile_path,'r','gbk','ignore') as f:
        for line in f:
            list = []  #创建字典对应候选的链表
            s=line.split("\t")  #以一个制表位分割一行
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
                        break
                # list.append((s1[2],s1[1]))      #往链表里添加候选
                str = ','.join(s1[2:])
                list.append(str)
                i=i+1
            art[s[2]] = (list,t)               #向对对象中插入正确的候选
    return  dic                 #dic为文章对应的词和候选集，ls为对应文章正确的的候选

#———————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

"""
结合本文档函数读取对应的数据  训练集和测试集合 外部获取数据API接口
"""
def Get_data(data_dir):  #参数数据目录
    data_info = get_data_dir(data_dir)
    test =[]
    tain =[]
    for i in range(len(data_info)):
        if(data_info[i][1]==0):
            test.append(createCDD(data_info[i][0]))
        if(data_info[i][1]==1):
            tain.append(createCDD(data_info[i][0]))
    print("数据读取完成")
    # test,   可返回 这里不用
    return tain,test
