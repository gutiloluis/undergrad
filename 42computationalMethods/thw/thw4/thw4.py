magic_n = raw_input("Por favor ingrese su numero magico: ")

print("Los multiplos de " + magic_n + " entre 1 y 1000 son: ")
n = int(magic_n)
sum = 0
nums = []
while(n<=1000):
    nums.append(n)
    #print n
    sum+=n
    n += int(magic_n)

print str(nums).replace('[','').replace(',','').replace(']','')
print "Su suma es: " + str(sum)
