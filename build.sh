clear
cd lang
flex --header-file=scanner.h -o scanner.cpp lex.l 
bison parser.y -o parser.cpp --defines=parser.h
cd ..
g++ -fno-stack-protector -g -o main *.cpp env/*.cpp users/*.cpp utils/exec/*.cpp utils/tools/*.cpp groups/*.cpp partitions/*.cpp disks/*.cpp lang/*.cpp nodes/*.cpp permissions/*.cpp