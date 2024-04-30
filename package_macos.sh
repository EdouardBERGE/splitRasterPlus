#! /bin/bash 

echo "Package splisdl for macos"

DIR=splitsdl.macos
make -f makefile.macos
mkdir $DIR
mv splitsdl ./$DIR/
otool -L $DIR/splitsdl  2>1  | egrep "SDL|png" | awk '{print $1}' | while read l; 
    do 
        file=`basename $l`; 
        install_name_tool -change $l @executable_path/$file $DIR/splitsdl;
        cp $l ./$DIR/
 done;