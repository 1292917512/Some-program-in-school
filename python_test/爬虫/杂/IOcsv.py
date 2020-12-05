import csv
def writer(filename,data):
    path = './data/'+filename
    csvFile = open(path,'a+')
    writer = csv.writer(csvFile)
    # 写入的内容都是以列表的形式传入函数
    writer.writerow(data,newline='')
    csvFile.close()