figures.png:	0.dat 1.dat 2.dat 3.dat 4.dat 5.dat 6.dat 7.dat 8.dat 9.dat
	python plotsrk4.py

0.dat:	a.out
	./a.out
1.dat:	a.out
	./a.out
2.dat:	a.out
	./a.out
3.dat:	a.out
	./a.out
4.dat:	a.out
	./a.out
5.dat:	a.out
	./a.out
6.dat:	a.out
	./a.out
7.dat:	a.out
	./a.out
8.dat:	a.out
	./a.out
9.dat:	a.out
	./a.out

a.out:	rk4.c
	cc rk4.c

clean:
	rm *dat figures.png a.out
