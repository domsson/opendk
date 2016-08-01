cd src
g++ -c *.cpp -std=c++11
g++ -o ../bin/opendk *.o -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
rm ./*.o
cd ..
