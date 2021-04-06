import numpy as np
import os
if __name__ == '__main__':
    dir= "E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\"
    sm = "gm_sm\\wned-"
    wiki = "gm_wiki\\wiki_"
    sm_wiki = "gm_sm_wiki\\"
    ls =['ace2004\\','aquaint\\','clueweb\\','msnbc\\','testa\\','testab\\','testb\\','wikipedia\\','testab\\']
    aim = ls[8]
    fnlist = os.listdir(dir+sm+aim)
    aimdir = dir + sm + aim
    aimdir2 = dir + wiki + aim
    print("路径加载完毕")
    for fn in fnlist:
        sm_g = np.loadtxt(aimdir+fn)
        wiki_g = np.loadtxt(aimdir2+fn)
        # for i in range(0,1500):
        #     for j in range(0, 1500):
        #         if(wiki_g[i][j]==1):
        #             t[i][j]=1
        #         else:
        #             t[i][j]=sm_g[i][j]
        np.savetxt("E:\\python_Object\\GCN_Entity_Linking\\data\\gm_adj\\gm_sm_wiki\\"+aim+fn,np.maximum(sm_g,wiki_g))
        # print(sm_g.shape())