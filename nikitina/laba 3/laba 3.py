# -*- coding: utf-8 -*-
import scipy
import numpy
import warnings

warnings.filterwarnings('ignore')

def Main():
            a = int(input('Введите кол-во переменных: '))
            b = int(input('Введите кол-во ограничений: '))
            values = numpy.array(list(map(int, input('Введите матрицу коэффициентов через запятую: ').split(','))))
            A_ub = values.reshape((b, a))
            cValues = numpy.array(list(map(int, input('Введите матрицу ограничений через запятую: ').split(','))))
            bValues = numpy.array(list(map(int, input('Введите прибыль через запятую: ').split(',')))) * (-1)
            A_ub_T = scipy.transpose(A_ub) * (-1)
            d = scipy.optimize.linprog(cValues, A_ub_T, bValues)
            print('Значение функции: ', round(d['fun'], 2))
            print('Текущий план: ', d['x'])
        

Main()