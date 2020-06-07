CC = gcc
COPTION = -g -Wall -Werror -Wextra

build: CLID
CLID: struct_utils.o intElem.o stringElem.o floatElem.o main.o
	$(CC) $(COPTION) $^ -o $@

main.o: main.c
	$(CC) $(COPTION) -c $^

struct_utils.o: struct_utils.c
	$(CC) $(COPTION) -c $^

intElem.o: intElem.c
	$(CC) $(COPTION) -c $^

floatElem.o: floatElem.c
	$(CC) $(COPTION) -c $^

stringElem.o: stringElem.c
	$(CC) $(COPTION) -c $^

run: CLID
	./CLID

clean:
	rm CLID *.o
