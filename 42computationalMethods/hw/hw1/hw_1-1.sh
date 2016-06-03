echo "1. En abril de 1995 hubo en promedio"
awk < monthrg.dat '{if($1==1995 && $2==4) print $4}'
echo -e "machas solares \n"

echo "2."
awk < monthrg.dat '{if($1>=1900 && $1<=1950 && $4>30) print $1, $4}' | wc -l
echo -e "meses entre 1900 y 1950 tuvieron mas de 30 manchas solares en promedio \n"

echo "3."
awk < monthrg.dat 'BEGIN{max=0;myear=0;mmonth=0} {if($4>max){max=$4;myear=$1;mmonth=$2}} END{print "El maximo numero de manchas solares fue", max, "y ocurrio el mes", mmonth, "del ano", myear}'
