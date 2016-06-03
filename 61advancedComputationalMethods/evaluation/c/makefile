plot.png : ../python/plot.py a.dat
	python $<

a.dat : a.out
	./$<

a.out : ode.c
	cc ode.c

.PHONY : clear
clear :
	rm a.dat a.out plot.png

