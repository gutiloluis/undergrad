Notes
=====

TODO
----
READ construction of high order symplectic operators by Yoshida 1990

gnuplot
-------
* to plot several sets in the same graph.

 plot 'salida.dat' u 1:(log10(abs($2-$3))), '' u 1:(log10(abs($2-$4))) 

* to plot only in a range.

plot [0:100] 'salida.dat' u 1:2
