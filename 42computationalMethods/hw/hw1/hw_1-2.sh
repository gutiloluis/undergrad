echo "1."
awk < notas_fisicaII_201320.dat  '{if($6>=60 && (($1<60 && $2>=60 && $3>=60) || ($2<60 && $1>=60 && $3>=60) || ($3<60 && $1>=60 && $2>=60))) print $6}' | wc -l
echo -e "estudiantes perdieron exactamente un parcial y ganaron la materia.\n"

echo "2."
awk < notas_fisicaII_201320.dat 'BEGIN{max_av=0;min_av=110} { if($6>=60 && ((($1+$2+$3)/3.0) > max_av ) ){max_av=(($1+$2+$3)/3.0)}; if($6>=60.0 && ( (($1+$2+$3)/3.0) < min_av ) ){min_av=(($1+$2+$3)/3.0)}} END{print "Entre los estudiantes que pasaron la materia, el mejor y el peor promedio de parciales fueron respectivamente", max_av, "y", min_av}'
