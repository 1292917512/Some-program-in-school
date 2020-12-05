import os
import re
# class Man(object):
#     #variable    class Attributes  类和类属性
#     a = 100
#     def __init__(self,sex,name):
#         #Initialization function
#         print("I gave birth")
#         eye =2
#         self.nose =1
#         self.sex =sex
#         self.name = name
#
#     #class function definition
#     def cry(self):
#         print("%s wasing crying"% self.name)
#     def laugh(self):
#         print("laughing")
#     def Judgesex(self):
#         print("Is a %s"% self.sex)
#     #Magic_method  魔术方法
#     def __str__(self):  #Effective when printing class   当输出这个类是起作用
#         return "This is a test"
#     def __repr__(self):  #when _str_ undefined   当方法_str_不起作用时 这个起作用
#         return "cuowu"
#     def __call__(self, *args, **kwargs): #Effective when class was called   当类被调用时生效
#         print("被调用")
# man = Man("man","ELF")
#
# man.Judgesex()
# man.cry()
# print(man)
# man()

# class Man(object):
#     def __new__(cls, *args, **kwargs):
#         if not hasattr(cls,"instance"):  #hasattr:See if the obeject contains "instrance",and return true if any
#has:有  sattr属性   判断此类中是否含有此属性
#             cls.instance = super().__new__(cls)
#         return cls.instance
#     def __init__(self,age):
#         self.age =age

# def file_test():   #error check
#     try:
#         with open("py.py","r"):
#             pass
#     except Exception as e:   #Exception：intercept all errors   Can choose other error   （The way prevents false interrupts）
#      Exception :包含所有可以被执行的错误命令，并将其返回
#         print(e,"error")
#     else:
#         print("运行正确")
#     finally:  #No matter what happens   无论发生错误与否这句话之后的都会在最后被调用
#         print("hollow world!")
# assert 1>2  #assert:incorrect will report an error   asssert：断言函数  、、 当判断值为假时会中断执行的函数
#
# file_test()

# class Rectangle:
#     color = "red"
#     def __init__(self,length,width):
#         self.length = length
#         self.width = width
#     def area(self):
#         areas = self.length*self.width
#         return areas
# r = Rectangle(100,100)
# print(r.color)
# # Judge the attribute is have
# print(hasattr(r,"length"))
# print(hasattr(r,"abc"))
# print(r.__getattribute__("color"))
#
# setattr(r,"bbb",200)  #contribute a new or change attribute    创建或者改变一个类属性
# r.__setattr__("ccc",3)
# r.ddd =111 #add by dirctor
# print(r.bbb)
# print(r.ccc)
# print(r.ddd)
# delattr(r,"color")
# try:
#     print(r.color)
# except Exception as e:
#     print(e)
#Custom property access 定制属性访问

# r = os.system("dir") #call system command

# a = input("places input you0r phone number:")
#
# r = re.match(r"1\d{10}",a).group()
# print(r)

# print(re.search("a","abc").group())


# 元字符 匹配点
#例1
# print(re.search(".","ab.bc").group())  #"."为元字符 表示匹配任意字符，
#
# print(re.search("\.","ab.bc").group()) #当"\."时表示匹配"."
"""
元字符标志
"."点：任意字符
"^"脱字符：开始标志
"$"美元符号：结束标志
"*"乘号：匹配任意多个  0或多
"+"加号：匹配任意多个不为0  1或多
"?"问号：有一个或者没有  0或1
"{}"前面字符出现个数  匹配次数
"[]"字符集合
"\"反斜杠：转义
"|"或运算  分支条件
"()"小括号：分组

"""

#re.findall() 查找所有
s = "<div class=\"wx-img-name\">毕业生就业指导中心</div></div>"

print(re.findall("<div(.*?)div>",s))
# print(re.search(r"<div(.*?)div>",s).group(1))   #()分组
"""
\d 匹配0~9的数字
\s 匹配任意的空白符，包括空格，制表符（Tab），换行符等
\w 匹配字母或数字或下划线或汉字等 \b表示单词的边界
\. 匹配。
\D,\S,\W,\B 是与小写的相反作用
\D  除数字外的所有字符 
"""
s ="nge_warmprompt = \"现在已经过凌晨了，身体是搞基的资本喔，早点休息哦！\""

# rule = re.compile("nge_warmprompt = \"(.*?)\"")
# print(rule.search(s).group(1))





"""
{}
{M,N} M和N为非负整数，其中M<=N表示前面的匹配M~N词
{M,} 表示需要匹配次
{，N}等价于{0~N}
{N}  表示需要匹配N次

[]
[.?*(){}]  匹配里面的这些符号
[0-9]  匹配0到9的数字相当于\d
[^\d]  匹配出数字以外的字符，相当于\D取反的意思
[a-z]  匹配所有的小写字母
[^a-z] 匹配费小写字母
|      相当于（of）分支条件
"""
# r = re.compile(r'\d+')  #提前设置规则
# a=r.findall("123av12")
# print(a)

# sub 替换
# r = re.sub(r"a","A","acvd123ddacc")
# print(r)
