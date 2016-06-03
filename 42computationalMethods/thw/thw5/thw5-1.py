import random

def obj_to_num(obj):
    if(obj.lower() == "piedra"):
        return 2
    elif(obj.lower() == "papel"):
        return 1
    elif(obj.lower() == "tijera"):
        return 0
    elif(obj.lower() == "salir"):
        return -2
    else:
        return -1

def num_to_obj(num):
    if(num == 2):
        return "Piedra"
    elif(num == 1):
        return "Papel"
    elif(num == 0):
        return "Tijera"


def winner(human, comp):
    
    ind = (comp - human)%3
    if(ind == 0):
        print "Empate"
    if(ind == 1):
        print "Usted gana"
    if(ind == 2):
        print "El computador gana"

print("PIEDRA, PAPEL O TIJERA\n")

while(True):
    human_choice = raw_input("Escoja una opcion: ")
    n = obj_to_num(human_choice)
    if(n==-2):
        exit()
    if(n>-1):
        print("Usted escoge " + human_choice)
        comp_choice = random.randint(0,2)
        print("el computador escoge "+ num_to_obj(comp_choice))
        winner(n,comp_choice)
        print("\n")
    elif(n==-1):
       print("Escoja 'piedra', 'papel', 'tijera' o 'salir'") 
       print("\n")
