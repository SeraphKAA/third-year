def get_selected_items_list(stuffdict, A = 2000):
      V, area, value = get_memtable(stuffdict)
      n = len(value)
      res = V[n][A]      # начинаем с последнего элемента таблицы
      a = A              # начальная площадь - максимальная
      items_list = []    # список площадей и ценностей
    
      for i in range(n, 0, -1):  # идём в обратном порядке
            if res <= 0:  # условие прерывания - собрали "рюкзак" 
                  break
            if res == V[i-1][a]:  # ничего не делаем, двигаемся дальше
                  continue
            else:
                  # "забираем" предмет
                  items_list.append((area[i-1], value[i-1]))
                  res -= value[i-1]   # отнимаем значение ценности от общей
                  a -= area[i-1]  # отнимаем площадь от общей
            
      selected_stuff = []

      # находим ключи исходного словаря - названия предметов
      for search in items_list:
            for key, value in stuffdict.items():
                  if value == search:
                        selected_stuff.append(key)
            
      return selected_stuff

def get_memtable(stuffdict, A = 2000):
      area, value = get_area_and_value(stuffdict)
      n = len(value) # находим размеры таблицы
      
      # создаём таблицу из нулевых значений
      V = [[0 for a in range(A+1)] for i in range(n+1)]

      for i in range(n+1):
            for a in range(A+1):
                  # базовый случай
                  if i == 0 or a == 0:
                        V[i][a] = 0

                  # если площадь предмета меньше площади столбца,
                  # максимизируем значение суммарной ценности
                  elif area[i-1] <= a:
                        V[i][a] = max(value[i-1] + V[i-1][a-area[i-1]], V[i-1][a])

                  # если площадь предмета больше площади столбца,
                  # забираем значение ячейки из предыдущей строки
                  else:
                        V[i][a] = V[i-1][a]       
      return V, area, value


def get_area_and_value(stuffdict):
    area = [stuffdict[item][0] for item in stuffdict]
    value = [stuffdict[item][1] for item in stuffdict]        
    return area, value




stuffdict = {'couch_s':(300,75), 
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



# stuff = get_selected_items_list(stuffdict)

# print(*stuff)
# print(sum([stuffdict[item][1] for item in stuff]))
