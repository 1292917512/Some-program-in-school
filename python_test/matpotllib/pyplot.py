# 1、安装python与numpy和matpotllib库
# 2、熟悉python的部分语法
#python -m pip install --user numpy scipy matplotlib ipython jupyter pandas sympy nose

import numpy as np
#和C语言的include是一样的都是调用库的，python里是用import
import matplotlib.pyplot as plt

#对于平常我们说的一个函数有定义域值域，对应关系，而我们一般说知道定义域和对应关系就可以知道值域
#定义域规定  main（argv*）
x = np.linspace(-3,3,50)

#然后我们要写出对应的关系
y1 = 2*x+1
y2 = x**2
# plt.figure()
# plt.plot(x,y1)
#我们最先决的条件已经设置好了，现在就是窗口问题了
#figure窗口设置和使用
plt.figure(num=2,figsize=(8,5))  #等会
#窗口设置

l1, = plt.plot(x,y2,color = 'blue',label = 'Up',linewidth = '1',linestyle = '--')
l2, = plt.plot(x,y1,color = 'red',label = 'Down',linewidth = '1')


#坐标上缺了什么东西我们可以自己添加的条件
#对轴的描述
plt.xlim(-1,2)
plt.ylim(-3,3)
plt.xlabel('I am x')
plt.ylabel('I am y')



#添加标注坐标
new_ticks =np.linspace(-1,2,5)
print(new_ticks)
plt.xticks(new_ticks)
plt.yticks([-1,0.5,1.5,1.22,3,],[r'$one\ ponit$',r'$tow \alpha$',r'$bad$',r'$normal$',r'$good$'])


#gca ='get current axis' spines脊柱
ax = plt.gca()
# 去除框架上和右的
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

#设定框架
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')
ax.spines['bottom'].set_position(('data',0))
ax.spines['left'].set_position(('data',0))

#添加标签
plt.legend(handles=[l1,l2,],labels=['aaa','bbb'],loc='best')
x0 = 0.5
y0 = 2*x0+1
plt.scatter(x0,y0,s=50,color='b')
plt.plot([x0,x0],[y0,0],'k--')

#做标记
plt.annotate(r'$2x+1=%s$'%y0,xy=(x0,y0),xycoords = 'data',xytext=(+30,-30),textcoords='offset points',fontsize= 16,arrowprops=dict(arrowstyle='->',connectionstyle='arc3,rad=.2'))
plt.text(x0,y0,r'$this\ is\ a\ point$',fontdict={'size':16,'color':'red'})
plt.show()


#标注添加
