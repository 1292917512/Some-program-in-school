import re
from bs4 import BeautifulSoup
import codecs
def getdata(html,year):
    # file=codecs.open("./data/2011年杭州房价走势图，2011杭州房价均价，杭州房价2011趋势查询-安居客.html",'rb')
    # html = file.read()
    bs = BeautifulSoup(html,"html.parser")
    b =bs.find_all("b")
    span = bs.select("a[class='nostyle']")
    r = re.compile(r'\d+')  #提前设置规则
    ls = [year]
    for i in span:
        s = i.contents
        s = r.findall(s[3].string)
        ls.append(int(s[0]))
    print("正在写入",year,"年")
    return ls
