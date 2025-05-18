DIR=$(dirname $(readlink -f "$1"))

echo  $DIR

if [ -f   $DIR/onscripter ]; then
    size=$(stat -c %s "$DIR/onscripter") 
    if [ "$size" -ne 856120 ]; then
         cp /usr/bin/onscripter $DIR/
    fi
    cd  $DIR
else
    size=$(stat -c %s "$1onscripter") 	
    cp /usr/bin/onscripter $DIR/
    cd  $DIR
fi

./onscripter
