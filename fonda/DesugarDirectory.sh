# pass in the name of the directory, and the name of the error file when running this script.
​
originalDirectory="$1"
logFile="$2"
​
​
for file in $(cd $originalDirectory; find -name "*.c")
do

  file="${file:1}"
  echo "Desugaring $OriginalDirectory$file"
  echo -e "Desugaring $OriginalDirectory$file" >> $logFile
  java superc.SugarC -D "_Noreturn=" -D "Pragma(x)=" -D __extension__= -restrictFreeToPrefix CONFIG_ -I "$originalDirectory\/include/" "$originalDirectory$file" > "$originalDirectory${file::-2}.desugared.c" 2>$logFile

  [ -s "$originalDirectory${file::-2}.desugared.c" ] || rm "$originalDirectory${file::-2}.desugared.c"
​
done
