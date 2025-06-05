#
#	Graph/
# 	├── src/
# 	│   ├── Grafo.cpp
#	│   ├── GrafoDir.cpp
# 	│   ├── GrafoNoDir.cpp
# 	│   ├── NodoVertice.cpp
# 	│   ├── NodoAdy.cpp
#   |   |   test.cpp
# 	|	└── makefile
# 	├── include/
# 	│   ├── Grafo.h
# 	│   ├── GrafoDir.h
# 	│   ├── GrafoNoDir.h
# 	│   └── NodoVertice.h
#	|	└── NodoAdy.h
# 	└── obj/


# compilador
CC      = g++
CFLAGS  = -Wall -Wextra -I../include  # flags para incluir headers waos
RM      = rm -f

# lugares
SRC_DIR = .
OBJ_DIR = ../objs
BIN_DIR = ..

# programa
TARGET_MAIN = $(BIN_DIR)/test

# los .cpp que necesitan los .o
SRCS = $(SRC_DIR)/test.cpp $(SRC_DIR)/GrafoNoDir.cpp $(SRC_DIR)/GrafoDir.cpp $(SRC_DIR)/NodoArco.cpp $(SRC_DIR)/NodoVertice.cpp 

# los objetos que necesita el programa
OBJS = $(OBJ_DIR)/test.o $(OBJ_DIR)/GrafoNoDir.o $(OBJ_DIR)/GrafoDir.o $(OBJ_DIR)/NodoArco.o $(OBJ_DIR)/NodoVertice.o 

# reglas
$(TARGET_MAIN): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

# los pony's
.PHONY: clean run

clean:
	@$(RM) $(OBJ_DIR)/$(OBJS) $(TARGET_MAIN)

run: $(TARGET_MAIN)
	@./$(TARGET_MAIN)
