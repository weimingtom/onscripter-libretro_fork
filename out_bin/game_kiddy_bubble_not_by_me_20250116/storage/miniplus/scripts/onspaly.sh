echo  "$1"

if [ ! -f "$1onscripter" ]; then
  cp  /storage/RA/onscripter "$1onscripter"
  chmod +x "$1onscripter"	
else
    size=$(stat -c %s "$1onscripter") 
    if [ "$size" -ne 807360 ]; then
         cp  /storage/RA/onscripter "$1onscripter"
         chmod +x "$1onscripter"
    fi
fi

cd "$1"

./onscripter
