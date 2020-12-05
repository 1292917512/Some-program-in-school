import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(-3,3,50)
y1 = x*np.log(x)
y2 = x*np.e**x
y3 = x/(np.log(x))
y4 = (np.log(x))/x
y5 = x/(np.e**x)
y6 = (np.e**x)/x
ax = plt.gca()
plt.plot(x,y1,color = 'red',label = '$xln(x)$',linewidth = '1')
plt.plot(x,y2,color = 'red',label = '$xe**x$',linewidth = '1',linestyle = '--')
plt.plot(x,y3,color = 'green',label = '$x/(np.log(x))$',linewidth = '1')
plt.plot(x,y4,color = 'green',label = '$(np.log(x))/x$',linewidth = '1',linestyle = '--')
plt.plot(x,y5,color = 'black',label = '$x/(np.e**x)$',linewidth = '1')
plt.plot(x,y6,color = 'black',label = '$(np.e**x)/x$',linewidth = '1',linestyle = '--')
# 去除框架上和右的
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
# ax.xaxis.set_ticks_position('bottom')
# ax.yaxis.set_ticks_position('left')
ax.spines['bottom'].set_position(('data',0))
ax.spines['left'].set_position(('data',0))
plt.legend()

plt.show()