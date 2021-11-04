CC = clang++
CFLAGS = -std=c++20 -O3 -Wall -DNDEBUG -march=native
O = main.o movegen.o

bit: $(O)
	$(CC) $(CFLAGS) -o $@ $(O)

main.o: main.cpp movegen.h
	$(CC) $(CFLAGS) -c main.cpp

movegen.o: movegen.cpp movegen.h
	$(CC) $(CFLAGS) -c movegen.cpp

clean:
	rm bit
