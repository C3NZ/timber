CXX = g++

compile: timber.cpp
	$(CXX) -c $?

build: timber.o
	$(CXX) $? -o game -lsfml-graphics -lsfml-window -lsfml-system


create: compile build

clean:
	rm *.o
