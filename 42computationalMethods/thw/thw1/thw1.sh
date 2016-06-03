echo "1."
wget https://dl.dropboxusercontent.com/u/9988568/hipparcos.tar.gz
tar -zxvf hipparcos.tar.gz

echo "2. Hay"
wc -l hipparcos.csv
echo "estrellas en el catalogo"

echo "3. El catalogo pesa"
wc -c hipparcos.csv
echo "bytes"

echo "4. Hay"
grep G2V hipparcos.csv | wc -l
echo "estrellas del mismo tipo espectral que el Sol (G2V)"

head -n 1 hipparcos.csv > EstrellasG2V.csv
grep G2V hipparcos.csv >> EstrellasG2V.csv

echo "6. El nuevo catalogo pesa"
wc -c EstrellasG2V.csv
echo "bytes"

tar -zcvf EstrellasG2V.tar.gz EstrellasG2V.csv

