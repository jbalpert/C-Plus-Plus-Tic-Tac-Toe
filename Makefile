# build an executable named main.exe from main.cpp
all: main.cpp 
	g++ -g -Wall -o main.exe main.cpp

clean: 
	$(RM) main.exe