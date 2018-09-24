all: main.o bit_writer.o node.o bit_reader.o
	g++ -o huffman main.o bit_writer.o node.o bit_reader.o -std=c++11

main.o: main.cpp
	g++ -o main.o -c main.cpp -std=c++11

bit_writer.o: bit_writer.cpp
	g++ -o bit_writer.o -c bit_writer.cpp -std=c++11

bit_reader.o: bit_reader.cpp
	g++ -o bit_reader.o -c bit_reader.cpp -std=c++11

node.o: node.cpp
	g++ -o node.o -c node.cpp -std=c++11


clean:
	rm *.o huffman