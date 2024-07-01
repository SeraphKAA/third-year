objects = { 
            'product_1':(3,75), 
            'product_2':(5,80), 
            'bread':(4,100), 
            'humburger':(2,50), 
            'tomato':(2,40), 
            'purrage':(2,70), 
            'burger':(3,80),
            'bat':(2,30),
            'energy_drink':(1,30),
            'salad':(2,20)
}

def wight_cost(dct:dict)->tuple:

    weight = []
    cost = []

    for key in dct.keys():
        weight.append(dct[key][0])
        cost.append(dct[key][1])

    return(weight,cost)

def recur_act_select(s,f,i,n):
    m = i+1
    while m <= n and s[m-1] < f[i-1]:
        m = m+1
    if m <= n:
        print(m)
        return(recur_act_select(s,f,i,n))
    else:
        return None
    
print(recur_act_select(wight_cost(objects)[0],wight_cost(objects)[1],1,10))