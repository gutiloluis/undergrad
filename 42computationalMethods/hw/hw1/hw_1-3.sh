echo "1."
awk -F "\"*,\"*" '{countries[$2]++;delete countries["naz"]} END{for(var in countries) print var, countries[var]}' giro_2014.csv | wc -l
echo -e "nacionalidades diferentes participaron en el Giro.\n"

echo "2."
awk -F "\"*,\"*" '{teams[$3]++;delete teams["team"]} END{for(var in teams) print var, teams[var]}' giro_2014.csv | wc -l
echo -e "equipos diferentes participaron en el Giro.\n"

echo "3."
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($4<min){min=$4;min_player=$1}} END{print "Ganador etapa 1", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($5<min){min=$5;min_player=$1}} END{print "Ganador etapa 2", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($6<min){min=$6;min_player=$1}} END{print "Ganador etapa 3", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($7<min){min=$7;min_player=$1}} END{print "Ganador etapa 4", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($8<min){min=$8;min_player=$1}} END{print "Ganador etapa 5", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($9<min){min=$9;min_player=$1}} END{print "Ganador etapa 6", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($10<min){min=$10;min_player=$1}} END{print "Ganador etapa 7", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($11<min){min=$11;min_player=$1}} END{print "Ganador etapa 8", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($12<min){min=$12;min_player=$1}} END{print "Ganador etapa 9", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($13<min){min=$13;min_player=$1}} END{print "Ganador etapa 10", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($14<min){min=$14;min_player=$1}} END{print "Ganador etapa 11", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($15<min){min=$15;min_player=$1}} END{print "Ganador etapa 12", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($16<min){min=$16;min_player=$1}} END{print "Ganador etapa 13", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($17<min){min=$17;min_player=$1}} END{print "Ganador etapa 14", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($18<min){min=$18;min_player=$1}} END{print "Ganador etapa 15", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($19<min){min=$19;min_player=$1}} END{print "Ganador etapa 16", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($20<min){min=$20;min_player=$1}} END{print "Ganador etapa 17", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($21<min){min=$21;min_player=$1}} END{print "Ganador etapa 18", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($22<min){min=$22;min_player=$1}} END{print "Ganador etapa 19", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($23<min){min=$23;min_player=$1}} END{print "Ganador etapa 20", min, min_player}' giro_2014.csv 
awk -F "\"*,\"*" 'BEGIN{min=100000000;min_player="nobody"} {if($24<min){min=$24;min_player=$1}} END{print "Ganador etapa 21", min, min_player}' giro_2014.csv 
