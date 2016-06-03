import sys
import numpy as np
from scipy.linalg import eigh

nombreArchivoDatos=sys.argv[1]
file=open(nombreArchivoDatos,'r')
input=file.readlines()
file.close()

n_dimensions=3
n_measurements=len(input)

data=np.empty((n_dimensions,n_measurements,))

for i in range(n_measurements):

    datosLinea=input[i].split()

    for j in range(n_dimensions):
        
        datosLinea[j]=float(datosLinea[j])
        data.itemset((j,i),datosLinea[j])

covariance_matrix=np.cov(data)

#Imprime la matriz de covarianza
print covariance_matrix

w,u = eigh(covariance_matrix, overwrite_a = True)

#Imprime los valores y vectores propios en orden descendente de valores propios
print ( w[::-1])
print (u[:,::-1])

#Imprime los valores y vectores propios en orden ascendente de valores propios
print (w[::])
print (u[:,::])

out_name='results_pca.txt'
out=open(out_name,'w')

#Aqui va lo que se escriba en el archivo

out.close()
