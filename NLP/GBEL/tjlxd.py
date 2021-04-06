import codecs




def get_data(fname):
    numlist = [0,0,0,0,0,0,0,0,0]
    num_max = 0
    with codecs.open(fname,'r','gbk','ignore') as f:
        for line in f:
            line = line.split("\t")
            if(line[4]=='0\r\n'):
                continue
            num_max =num_max+1
            if(line[3]=='EMPTYCAN'):
                continue
            if(float(line[3])<0.3):
                numlist[0] = numlist[0]+1
            else:
                if(float(line[3])<0.4):
                    numlist[1] = numlist[1] + 1
                else:
                    if(float(line[3])<0.5):
                        numlist[2] = numlist[2] + 1
                    else:
                        if(float(line[3])<0.6):
                            numlist[3] = numlist[3] + 1
                        else:
                            if(float(line[3])<0.7):
                                numlist[4] = numlist[4] + 1
                            else:
                                if(float(line[3])<0.8):
                                    numlist[5] = numlist[5] + 1
                                else:
                                    if(float(line[3])<0.9):
                                        numlist[6] = numlist[6] + 1
                                    else:
                                        if (float(line[3]) < 1):
                                            numlist[7] = numlist[7] + 1
                                        else:
                                            if(float(line[3])==1):
                                                numlist[8] = numlist[8] + 1
    return numlist,num_max


if __name__ == '__main__':
    aim = ['ace2004-Pr','clueweb-Pr','msnbc-Pr','aquaint-Pr']
    dir = "E:\\python_Object\\GCN_Entity_Linking\\data\\lxd\\"
    dic ={}
    for aimname in aim:
        numlist, all= get_data(dir+aimname)
        dic[aimname,all] = numlist
    f = open("E:\\python_Object\\GCN_Entity_Linking\\lxd.txt",'w')
    for key in dic:
        f.write(str(key[0])+'_'+str(key[1])+":\t")
        for num in dic[key]:
            f.write(str(num)+"\t")
        f.write("\n")
    f.close()