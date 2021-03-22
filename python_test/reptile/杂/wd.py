import copy

def get_wd(ls):
    k = 0
    ls2 = copy.deepcopy(ls)
    mun =len(ls)
    for i in range(mun):
        for j in range(i,mun):
            k += 1
            if ls[i]==ls[j]:
                ls2.append(ls[i]+'^2')
            else:
                ls2.append(ls[i]+'_'+ls[j])

    print(mun,"个因素数据平方总计参数",k)
    return ls2