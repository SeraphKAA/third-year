import numpy as np
from numpy.core.fromnumeric import shape
result = ''

def Something(txt1, txt2):
    global result
    X = list(txt1)
    Y = list(txt2)

    def LCS_Len(X,Y):
        m = len(X)+2
        n = len(Y)+2
        c = np.zeros((m,n),dtype=int)
        b = np.zeros((m,n),dtype=str)

        for i in range(m):
            c[i,0] = 0
            if i >= 2:
                b[i,0] = X[i-2]
            b[i,1] = 0
        for j in range(n):
            c[0,j] = 0
            if j >= 2:
                b[0,j] = Y[j-2]
            b[1,j] = 0

        b[0][0] = ' '
        b[0,1] = 'Y'
        b[1,0] = 'X'
        for i in range(2,m):
            for j in range(2,n):
                if X[i-2] == Y[j-2]:
                    c[i,j] = c[i-1,j-1]+1
                    b[i][j] = "↖"
                elif c[i-1,j] >= c[i,j-1]:
                    c[i,j] = c[i-1,j]
                    b[i][j] = "↑"
                else:
                    c[i,j] = c[i,j-1]
                    b[i][j] = "←"
        counter = 0
        for i in range(m):
            for j in range(n):
                if b[i][j] == "↑" or b[i][j] == "←":
                    counter += 1
        print(counter)
        s = 2**counter
        print(s)
        return c, b 
    
    mat_int, mat_str = LCS_Len(X,Y)
    print(mat_str)
    mat_str = mat_str[1:,1:]

    LCS_print(mat_str,X,len(X),len(Y))
    return result


def LCS_print(b,X,i,j):
    global result
    if (i == 0) or (j == 0):
        return result
    if b[i,j] == "↖":
        LCS_print(b,X,i-1,j-1)
        result += X[i-1]
    elif b[i,j] == "↑":
        LCS_print(b,X,i-1,j)
    else:
        LCS_print(b,X,i,j-1)




