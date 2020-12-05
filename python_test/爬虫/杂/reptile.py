import requests
import re
import bs4
from bs4 import BeautifulSoup

#请求
"""
print(r.status_code) #HTTP请求的返回状态，200表示连接成功，404或者其他表示失败
print(r.text)  #HTTP相应内容的字符串形式，即，url对应的页面内容
print(r.encoding) #从HTTP header中猜测的响应内容编码方式
print(r.apparent_encoding) #从内容中分析出响应的内容编码方式（备选编码方式）
print(r.content) #HTTP响应内容的二进制形式

"""

#异常
"""
requests.ConnectionError #网络连接错误异常，如DNS查询失败，拒绝连接等
requests.HTTPError #HTTP错误异常
requests.URLRequired #URL缺失异常
requests.TooManyRedirects #超过最大重定向次数，产生重定向异常
requests.ConnectTimeout #链接远程服务器超时异常
requests.Timeout #请求URL超时，产生超时异常

"""
#requests七大方法
"""
requests.request() #构造一个请求，支撑一下各方法的基础方法
requests.get()   #获取HTML网页的主要方法，对应于HTTP的GET
requests.head()  #获取HTML网页头信息的方法，对应于HTTP的HEAD
requests.post()  #向HTML网页提交POST请求的方法，对应于HTTP的POST
requests.put()  #向HTML网页提交PUT请求的方法，对应与HTTP的PUT
requests.patch() #向HTML网页提交局部修改清酒，对应于HTTP的PATCH
requests.delete() # 向HTMl网页提交删除请求，对应于HTTP的DELETE
"""
"""
**kwargs：控制访问的参数，均为可选项

访问控制参数
params 更改url                    cookies 记录访问账户信息         proxies 访问服务器
data  数据，字典、直接序列或文件    auth                            allow_redirects:True/False,默认为true重定向开关    
json  JSON格式数据，Request的内容  files    文件传输                stream：True/False，默认为True，获取内容立刻下载开关    
headers  更改访问浏览器            timeout  超时标志                cert：本地SSL证书路径 veriFy：True/False，默认为True，认真SSL证书开关
"""
# r.raise_for_status() #如果不是200，产生异常requests.HTTPError
#一般框架
# def getHTMLText(url):
#     try :
#         r = requests.get(url,timeout =10)
#         r.raise_for_status()
#         r.encoding =r.apparent_encoding
#         return  r.text
#     except:
#         return "产生异常"
# if __name__ == "__main__":
#     url = "https://item.jd.com/100010892480.html"
#     print(getHTMLText(url))

#搜索框架
# keyword = "python"
# url = "http://www.baidu.com/s"
# try:
#     kv = {'wd': keyword}
#     r = requests.get(url,params=kv)
#     print(r.request.url)
#     r.raise_for_status()
#     print(len(r.text))
# except:
#     print("爬取失败")


#图片爬取
# import os
# root ="D://pics//"
# url = "https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9QbjRTbTBSc0F1aWFlVDNmR3hXN05naDlZcndTMjNIWWQxaktBanl1R0R4QUE0NWVkYUNRMFJPZ1RiUFpFaldHNmZsUW42ZzM4cmxsaWN3bnZVdXhqMU5BLzY0MA?x-oss-process=image/format,png"
# path = root +url.split('/')[-1]
# try:
#     if not os.path.exists(root):
#         os.mkdir(root)
#     if not os.path.exists(path):
#         r = requests.get(url)
#         with open(path,'wb')as f:
#             f.write(r.content)
#             f.close()
#             print("文件保存成功")
#     else:
#         print("文件已经存在")
# except:
#     print("爬取失败")

#地址与归属地查询

# url ="http://www.ip138.com/iplookup.asp"
# ip ='119.3.70.188'
# kv = {'ip':ip}
# r = requests.get(url,params=kv)
# print(r.url)
# print(r.status_code)
# r.encoding=r.apparent_encoding
# print(r.text)
# rule = re.compile("<li>(.*?)</li><li>")
# a = rule.search(r.text).group(1)
# print(a)
# url = "http://python123.io/ws/demo.html"
# Dome = requests.get(url)
# Dome.status_code
# soup = BeautifulSoup(Dome.text,"html.parser")
"""
HTML文件是树状结构，用soup库就是将结构进行整理成树，便于访问和操作,遍历
.comtents 子节点的列表，将<tag>所有的儿子节点存入列表[内容]
.children 子节点的迭代类型，与.comtents类似，用于循环遍历儿子节点
.descendants 子孙节点的迭代类型，包含所有子孙节点，用于循环遍历
.parent 节点的父亲标签
.parents 节点的先辈变迁的迭代类型，用于循环遍历先辈节点
.next_sibling 返回按照HTML文本顺序的下一个平行节点标签
.previous_sibling 返回按照HTML文本顺序的上一个平行节点标签
.next_siblings  迭代类型，返回按照HTML文本顺序的后续所有平行节点标签
.previous_siblings 迭代类型，返回按照HTML文本顺序的前序所有平行节点标签
"""
# 遍历节点
# for child in soup.body.descendants:      #遍历所有子孙节点   下行
#     print(child)
# for child in soup.body.children:         #遍历所有儿子节点    下行
#     print(child)
# for parent in soup.a.parents:          #遍历所有父亲节点    上行
#     if parent is None:
#         print(parent)
#     else:
#         print(parent.name)
# for sibing in soup.a.next_siblings#(.previous_siblings)   平行遍历节点
#     print(sibing)
"""
HTML :Hyper Text Markup language  超文本标记语言

XML :eXtensible Markup language   扩展标记语言
<name>...</name>   <name/> <!-- -->

Json ： JavaScript Object Notation   
有类型的键值对表达 key：vaule（可以嵌套）

YAML YAML Aint't Markup language
无类型的键值对表达 key：baule   text：|
"""


"""
<>.find_all(name(标签名字),attrs（对应属性，可标记属性搜索）,recursive（是否对子孙节点遍历 默认为true）,string（<>..</>中字符串区域的检索字符串）,*kwargs)

# for link in soup.find_all('a'):
#     print(link.get('href'))

for tag in soup.find_all(re.compile('b')):  #可以用正则表达式来提取有关的内容
    print(tag.name)
soup.find_all(string = re.compile("python"))  //用正则找其中有的字符串文本

"""

#爬取大学排名
# def getHTMLText(url):
#     try:
#         r = requests.get(url,timeout =10)
#         r.raise_for_status()
#         r.encoding = r.apparent_encoding
#         return r.text
#     except:
#         return ""


# def fillUnivList(ulist,html):
#     soup = BeautifulSoup(html,"html.parser")
#     for tr in soup.find('tbody').children:
#         if isinstance(tr, bs4.element.Tag):
#             tds = tr('td')
#             ulist.append([tds[0].string,tds[1].string,tds[2].string])


# def printUnivList(ulist,num):
#     tplt ="{0:<10}\t{1:<25}\t{2:<10}"
#     print(tplt.format("排名","学校名称","位置"),chr(12288))   #填充格式
#     for i in range(num):
#         u = ulist[i]
#         print(tplt.format(u[0],u[1],u[2]),chr(12288))
#     print("suc"+str(num))


# def main():
#     uinfo =[]
#     url ="http://www.zuihaodaxue.cn/Greater_China_Ranking2019_0.html"
#     html= getHTMLText(url)
#     fillUnivList(uinfo,html)
#     printUnivList(uinfo,20)
# main()



#
# def fillUnivList(ulist,html):
#     soup = BeautifulSoup(html,"html.parser")
#     for tr in soup.find('tbody').children:
#         if isinstance(tr, bs4.element.Tag):
#             tds = tr('td')
#             ulist.append([tds[0].string,tds[1].string,tds[2].string])


# def printUnivList(ulist,num):
#     tplt ="{0:<10}\t{1:<25}\t{2:<10}"
#     print(tplt.format("排名","学校名称","位置"),chr(12288))   #填充格式
#     for i in range(num):
#         u = ulist[i]
#         print(tplt.format(u[0],u[1],u[2]),chr(12288))
#     print("suc"+str(num))


# def main():
#     uinfo =[]
#     url ="http://www.zuihaodaxue.cn/Greater_China_Ranking2019_0.html"
#     html= getHTMLText(url)
#     fillUnivList(uinfo,html)
#     printUnivList(uinfo,20)


# url ="https://coronavirus.1point3acres.com/zh"
# def getHTML(url):
#     try:
#         headers = {
#             'User-Agent': 'User-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'}
#         r = requests.get(url,headers =headers ,timeout = 10)
#         r.raise_for_status()
#         r.encoding =r.apparent_encoding
#         return r.text
#     except:
#         print("错误")

# text=getHTML(url)

# soup = BeautifulSoup(text,"html.parser")

# print(soup)



# tx = t.search(text)
# print(tx.group(1))