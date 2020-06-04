CC = gcc
COPTION = -g -Wall -Werror -Wextra

build: tema1

tema1: struct_utils.o intElem.o stringElem.o floatElem.o main.o
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

run: tema1
	./tema1

clean:
	rm tema1 *.o
