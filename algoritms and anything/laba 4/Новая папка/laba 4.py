objects = {'couch_s':(300,75), 
             'couch_b':(500,80), 
             'bed':(400,100), 
             'closet':(200,50), 
             'bed_s':(200,40), 
             'desk':(200,70), 
             'table':(300,80),
             'tv_table':(200,30),
             'armchair':(100,30),
             'bookshelf':(200,60), 
             'cabinet':(150,20),
             'game_table':(150,30),
             'hammock':(250,45),
             'diner_table_with_chairs':(250,70),
             'stools':(150,30),
             'mirror':(100,20),
             'instrument':(300,70),
             'plant_1':(25,10),
             'plant_2':(30,20),
             'plant_3':(45,25),
             'sideboard':(175,30),
             'chest_of_drawers':(25,40),
             'guest_bed':(250,40),
             'standing_lamp':(20,30), 
             'garbage_can':(30,35), 
             'bar_with_stools':(200,40), 
             'bike_stand':(100,80),
             'chest':(150,25),
             'heater':(100,25)
            }

def generate_objects(n:int,cost_max,weight_max) -> dict:
    import random
    lst = []
    for i in range(n):
        w = random.randint(1,weight_max)
        c = random.randint(1,cost_max)
        lst.append((i,w,c,c/w))

    sorted_lst = {}
    sorted_lst = sorted(lst,key = lambda rel: rel[3],reverse=True)

    for it in range(len(sorted_lst)):
        print("{} || {}".format(sorted_lst[it][0],sorted_lst[it][1:]))

    dct = {}
    for val in sorted_lst:
        dct[val[0]] = val[1:]

    return(dct)

def dict_seperate(dct:dict)->tuple:

    weight = []
    cost = []
    relative = []

    for key in dct.keys():
        weight.append(dct[key][0])
        cost.append(dct[key][1])
        relative.append(dct[key][2])

    return(weight,cost,relative)

def table_generate(dct:dict, size:int) -> tuple:

    # Подготовка данных
    weight, cost, relative = dict_seperate(dct)
    n = len(cost)
    V = []
    # Заполняем таблицу нулями 
    for i in range(n+1):
        lst = []
        for j in range(size+1):
            lst.append(0)
        V.append(lst)
    # Построение таблицы
    for i in range(n+1):
            for j in range(size+1):
                if i == 0 or j == 0:
                    V[i][j] = 0
                elif weight[i-1] <= j:
                    V[i][j] = max(cost[i-1] + V[i-1][j-weight[i-1]], V[i-1][j])
                else:
                    V[i][j] = V[i-1][j]   
    for i in V:
        print(i)
    return V, weight, cost

def bag(weight,cost,n,W,relative):
    sum = 0
    for i in range(weight):
        if W>weight[i]:
            sum += cost[i]
        else:
            sum += W/(weight[i]+relative[i])
            break
    return(sum)

print("Пареметры предметов (номер = (вес,цена,цена 1 еденицы веса на цену))")
dct = generate_objects(5,20,5)
print("_"*40+"\n")

def bag(items,max_bag_weight):
    weight,cost,relative = dict_seperate(items)
    print(f"Общая вместимость ранца : {max_bag_weight} кг")
    dct_of_counts = {}

    weight_now = 0
    best_price = 0
    names = list(items.keys())
    max_bag_weight = float(max_bag_weight)

    while weight_now <= max_bag_weight:
        for i in range(len(weight)):
            if weight_now + weight[i] <= max_bag_weight: 
                best_price += cost[i]
                weight_now += weight[i]
                if f"Предмет #{names[i]}" in dct_of_counts.keys():
                    dct_of_counts[f"Предмет #{names[i]}"][0] += weight[i]
                    dct_of_counts[f"Предмет #{names[i]}"][1] += cost[i]
                else:
                    dct_of_counts[f"Предмет #{names[i]}"] = [weight[i],cost[i]]
                #    print("Общий вес на данный момент : ",  weight_now)

            else:
                while weight_now <= max_bag_weight:
                    for i in range(len(relative)):
                        if weight_now <= max_bag_weight:
                            weight_now += weight[i]/cost[i] 
                            best_price += relative[i]
                            if f"Предмет #{names[i]}" in dct_of_counts.keys():
                                dct_of_counts[f"Предмет #{names[i]}"][0] += weight[i]/cost[i]
                                dct_of_counts[f"Предмет #{names[i]}"][1] += relative[i]
                            else:
                                dct_of_counts[f"Предмет #{names[i]}"] = [weight[i]/cost[i],relative[i]]
                        else:
                            break
    print("\n")
    count_list = []
    for i in range(len(weight)):
        value = dct_of_counts[f"Предмет #{names[i]}"][0]/weight[i] * 100
        count_list.append(value)
    for i in range(len(dct_of_counts.keys())):
        print(
            f"{list(dct_of_counts.keys())[i]}\
            ||Количество предмета: {count_list[i]}%\
            ||Вес: {dct_of_counts[list(dct_of_counts.keys())[i]][0]} кг\
            ||Цена: {dct_of_counts[list(dct_of_counts.keys())[i]][1]} $\
                "
        )
    return(best_price)

print("Максимальная стопимость рюкзака = ",bag(dct,20))