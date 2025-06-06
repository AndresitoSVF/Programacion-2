target = RUN
CC = g++
CFLAGS = -Wall -Wextra -std=c++98
LDFLAGS = -lm -lpthread

.PHONY: all clean run cleanall

all: run
	
run: $(target)
	./$(target)

$(target): testNodo.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(target)