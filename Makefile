clean:
	rm -f *.o
	rm -f Client
	rm -f Server

all:
	make clean
	g++ Client.cpp -o Client
	g++ Server.cpp -o Server