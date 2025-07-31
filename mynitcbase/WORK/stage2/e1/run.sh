NITCBASE_DIR=$HOME/NITCbase/mynitcbase/
OUTPUT_DIR=$PWD
cp main.cpp $NITCBASE_DIR/temp.cpp
cd $NITCBASE_DIR 
mv main.cpp prev_main.cpp
mv temp.cpp main.cpp
make
./nitcbase > $OUTPUT_DIR/output.txt
rm main.cpp build/main.o
mv prev_main.cpp main.cpp
make
#./nitcbase
cd -
