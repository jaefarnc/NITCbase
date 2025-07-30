NITCBASE_DIR=$HOME/NITCbase/mynitcbase/
OUTPUT_DIR=$PWD
cp e1.cpp $NITCBASE_DIR
cd $NITCBASE_DIR 
mv main.cpp prev_main.cpp
mv e1.cpp main.cpp
make
./nitcbase > $OUTPUT_DIR/output.txt
rm main.cpp build/main.o
mv prev_main.cpp main.cpp
make
#./nitcbase
cd -
