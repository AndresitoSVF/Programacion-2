TARGET = RUN
CC = g++
CFLAGS = -march=native -O3 -Wall -Wextra -std=c++98
LDFLAGS = -lm -lpthread

.PHONY: all clean run cleanall

all: $(TARGET)
	
run: $(TARGET)
	./$(TARGET)

$(TARGET): testNodo.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(TARGET)
