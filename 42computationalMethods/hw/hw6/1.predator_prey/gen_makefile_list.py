i = 30
while(i>0):
    print("poblaciones_"+str(i)+"_20.pdf:\tpoblaciones_"+str(i)+"_20.dat")
    print("\tpython plot_poblaciones.py poblaciones_"+str(i)+"_20.dat")

    print("poblaciones_"+str(i)+"_20.dat:\trunge_kutta.x")
    print("\t./runge_kutta.x "+str(i)+" 20\n")
    i-=1
