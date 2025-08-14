TARGET = RUN
CC = g++
INC_PATHS = -I. -I./LPC
CFLAGS = $(INC_PATHS) -march=native -O3 -Wall -Wextra -std=c++98 -I../LPC
LDFLAGS = -lm
MAIN = main
HEADERS = Lista.h Pila.h Nodo.h Cola.h

.PHONY: all clean run cleanall

all: $(TARGET)
    
run: $(TARGET)
	./$(TARGET) < entrada.txt > salida.txt

$(TARGET): $(MAIN).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CFLAGS) -c $(MAIN).cpp -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(TARGET)
