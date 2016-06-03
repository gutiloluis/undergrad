def tribonacci(n):
    if(n==1 or n==2 or n==3):
        return 1
    else:
        return tribonacci(n-1)+tribonacci(n-2)+tribonacci(n-3)

arr = []
def tribonacci_series(N):
    for i in range(1,N+1):
        arr.append(tribonacci(i))
    print arr

N = int(raw_input("Introduzca el numero de terminos de la serie de 'Tribonacci': "))
tribonacci_series(N)
