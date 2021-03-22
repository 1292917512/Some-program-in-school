import numpy as np
# import matplotlib.pyplot as plt
import pandas as pd
from wd import get_wd
ls =['xxsrs','dj','rkmd','rks','pjxz','kzpsr']
ls2 = ['xxsrs','dj','pjxz']
from  sklearn.model_selection import train_test_split,cross_val_score
from  sklearn.linear_model import  lasso_path,ridge,LinearRegression as LR
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import r2_score,explained_variance_score as EVS,mean_absolute_error as MSE
from sklearn.preprocessing import PolynomialFeatures
np.set_printoptions(suppress=True)
data =  pd.read_csv('./data/fjsj.csv')
x = data[ls]
y = data['fj']

x_train,x_test,y_train,y_test =train_test_split(x,y,test_size=0.2,random_state=42)
reg =LR().fit(x_train,y_train)
yhat = reg.predict(x_test)

print("多元线性回归参数线性")
print(reg.coef_)

print("多元线性回归截距")
print(reg.intercept_)

print("多元线性回归拟合度")


# print(np.sqrt(MSE(y_test,yhat))/y_test.mean())
# print(-cross_val_score(reg,x,y,cv=5,scoring="neg_mean_squared_error"))
# print(cross_val_score(reg,x,y,cv=5,scoring="r2").mean())
#
# r2_score(y_test,yhat)
# r2 =reg.score(x_test,y_test)
print(-cross_val_score(reg,x,y,cv=5,scoring="neg_mean_squared_error"))


po = PolynomialFeatures(degree=2,interaction_only=False,include_bias=False)
x_poly = po.fit_transform(x)
# pd.DataFrame(x_poly).head()
x_poly = pd.DataFrame(x_poly,columns=[get_wd(ls)])
x_train2,x_test2,y_train2,y_test2 =train_test_split(x_poly,y,test_size=0.3,random_state=42)
reg2 =LR().fit(x_train2,y_train2)
yhat2 = reg2.predict(x_test2)
print("多元非线性回归参数线性")
print(reg2.coef_)
print("多元非线性回归截距")
print(reg2.intercept_)
print("多元非线性回归拟合度")
print(MSE(y_test2,yhat2))
print(np.sqrt(MSE(y_test2,yhat2))/y_test2.mean())

print(-cross_val_score(reg2,x,y,cv=5,scoring="neg_mean_squared_error"))
print(cross_val_score(reg,x,y,cv=5,scoring="r2").mean())
#
print(r2_score(y_test,yhat))
r2 =reg.score(x_test,y_test)
# print(r2)