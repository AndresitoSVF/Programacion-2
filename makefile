TARGET = RUN
CC = g++
INC_PATHS = -I. -I./Trees
CFLAGS = $(INC_PATHS) -march=native -O3 -Wall -Wextra
LDFLAGS = -lm
MAIN = 
#testArbolBB
#testRecorridosAB
#testArbolN
#testArbolB

.PHONY: all clean run cleanall

all: $(TARGET)
    
run: $(TARGET) 
	./$(TARGET)

$(TARGET): $(MAIN).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CFLAGS) -c $(MAIN).cpp -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(TARGET)
