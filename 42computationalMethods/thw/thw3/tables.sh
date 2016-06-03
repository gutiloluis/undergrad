wget https://raw.githubusercontent.com/jngaravitoc/HerramientasComputacionales/master/Homeworks/HW3/ggiro.csv
rm table.tex
touch table.tex
echo "\documentclass[10pt]{article}" >> table.tex
echo "\usepackage[hmargin=2.0cm, vmargin=1cm]{geometry}" >> table.tex
echo "\begin{document}" >> table.tex

echo "\begin{table}[h]" >> table.tex
echo "\centering" >> table.tex
echo "\begin{tabular}{c c c c c c c c c}" >> table.tex
echo "\hline" >> table.tex

sed 's/,/ \&/g' ggiro.csv > giro1.txt
sed 's/\"/ \ /g' giro1.txt > giro2.txt
sed 's/$/ \\\\/g' giro2.txt >> table.tex

echo "\end{tabular}" >> table.tex
echo "\end{table}" >> table.tex
echo "\end{document}" >> table.tex

rm giro1.txt
rm giro2.txt

latex table.tex
pdflatex table.tex
evince table.pdf &

rm ggiro.csv*
