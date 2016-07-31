cd src
g++ -c *.cpp -std=c++11
g++ -o ../bin/opendk *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
rm ./*.o
cd ..
