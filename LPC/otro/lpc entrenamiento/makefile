
LPC_DIR = lpcDir
CFLAGS = -O3 -flto -s -I$(LPC_DIR)

MY_LIBS = $(wildcard $(LPC_DIR)/*)
HEADERS = lpcDir/List.hpp lpcDir/Queue.hpp lpcDir/Stack.hpp
NO_HEADERS = lpcDir/List.cpp lpcDir/Queue.cpp lpcDir/Stack.cpp
OBJECTS = $(patsubst $(LPC_DIR)/%.cpp, object/%.o, $(NO_HEADERS))
TARGET = main.cpp
OUTPUT = lpc

all: $(OUTPUT) 

$(OUTPUT): $(TARGET) $(HEADERS) $(OBJECTS)
	g++ $(CFLAGS) -o $(OUTPUT) $(TARGET) $(OBJECTS)

object/%.o: lpcDir/%.cpp
	g++ $(CFLAGS) -o $@ -c $<

run:  $(OUTPUT)
	./$(OUTPUT) < entrada.txt > out.txt

clean:
	rm -f ./$(OUTPUT) object/*


.PHONY: clean run find_error generic_types
