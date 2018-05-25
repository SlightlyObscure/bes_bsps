all: 
	g++ myfind.cpp -o myfind -std=c++11 -Wall

clean:
	rm -f myfind
