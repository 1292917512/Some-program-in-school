import numpy as np
import torch
from data_process.data_process_function import Get_data

if __name__ == '__main__':
    DIR = "E:\python_Object\GCN_Entity_Linking\data"  # 保存训练集和测试集的路径
    DIR_bert = "E:\\python_Object\\GCN_Entity_Linking\\data\\sm_unbert\\"
    DIR_loss = "E:\\python_Object\\GCN_Entity_Linking\\data\gm_loss\\"
    trainlist,testlist = Get_data(DIR)
    num=0
    zq = 0
    for art in testlist[5]:
        bert = np.loadtxt(DIR_bert+art)
        loss = np.loadtxt(DIR_loss+art)
        for start in range(0, len(bert), 30):
            end = start + 30
            B = bert[start:end]
            L = loss[start:end]
            if(np.max(L)==0):
                continue
            num = num+1
            if(np.argmax(B)==np.argmax(L)):
                zq = zq+1
    print("Accuracy: {:.2%}".format(zq / num))

