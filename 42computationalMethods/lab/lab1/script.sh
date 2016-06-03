awk < notas_fisicaII_201320.dat '{if($1>=60) print $1}' | wc -l 
echo "estudiantes pasaron el primer parcial"

awk < notas_fisicaII_201320.dat '{if($1>=60 && $5<60 && $6>=60) print $6}' | wc -l
echo "estudiantes pasaron el primer parcial, perdieron el final y pasaron la materia"

awk < notas_fisicaII_201320.dat '{if($6>=60 && ($1<60 || $2<60 || $3 < 60)) print $6}' | wc -l
echo "estudiantes perdieron al menos un parcial y pasaron la materia"

awk < notas_fisicaII_201320.dat '{ if($6>=60 && ( ($1>=60 && $2>=60 && $3<60) || ($1>=60 && $3>=60 && $2<60) || ($2>=60 && $3>=60 && $1<60))) print $1, $2, $3, $6}' | wc -l
echo "estudiantes pasaron solamente dos parciales y pasaron la materia"
