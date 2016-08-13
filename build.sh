cd src
g++ -c *.cpp -std=c++11 -Wall
g++ -c engine/opengl/*.cpp -std=c++11 -Wall
g++ -c engine/level/*.cpp -std=c++11 -Wall
g++ -c utils/*.cpp -std=c++11 -Wall
g++ -o ../bin/opendk *.o -lGL -lGLEW  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
rm ./*.o
cd ..
