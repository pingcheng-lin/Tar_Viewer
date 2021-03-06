all: dep
	g++ -std=c++11 main.cpp stack.o -o output1
	g++ -std=c++11 main2.cpp stack.o -o output2
dep:
	g++ -std=c++11 -c stack.cpp -o stack.o
clean: 
	rm -f *.o output1 output2
