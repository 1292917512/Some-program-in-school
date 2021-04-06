import os

if __name__ == '__main__':
    path = "E:\\python_Object\\GCN_Entity_Linking\\data\\sm_bert"
    filelist = os.listdir(path)
    for filename in filelist:  #filename获得的文件名
        # 设置旧文件名（就是路径+文件名）
        oldname = path + os.sep + filename# os.sep添加系统分隔符

        newname = path + os.sep + filename.replace(" ","") # 设置新文件名
        os.rename(oldname, newname)  # 用os模块中的rename方法对文件改名
        print(oldname, '======>', newname)