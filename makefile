all: dep
	g++ -std=c++11 main.cpp mytar.o -o mytar
dep:
	g++ -std=c++11 -c mytar.cpp -o mytar.o
clean:
	rm -f *.o mytar