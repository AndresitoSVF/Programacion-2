#
#	Graph/
# 	├── src/
# 	│   ├── Grafo.cpp
#	│   ├── GrafoDir.cpp
# 	│   ├── GrafoNoDir.cpp
# 	│   ├── NodoVertice.cpp
# 	│   ├── NodoAdy.cpp
#   |   |   
# 	|	└── 
# 	├── include/
# 	│   ├── Grafo.h
# 	│   ├── GrafoDir.h
# 	│   ├── GrafoNoDir.h
# 	│   └── NodoVertice.h
#	|	└── NodoAdy.h
# 	└── obj/


# compilador
CC      = g++
CFLAGS  = -Wall -Wextra -Iinclude -Isrc # flags para incluir headers waos -std=c++98
LDFLAGS = -lm
RM      = rm -f
SRCS = $(wildcard src/*.cpp) # Busca todos los archivos .cpp en la carpeta src
OBJS = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) # Crea la lista de objetos en el directorio obj

# lugares
OBJ_DIR = obj

# programa
OUTPUT = test


all: $(OBJ_DIR) $(OUTPUT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# reglas
$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# los pony's
.PHONY: clean run all check  check_automatically

clean:
	@$(RM) $(OBJ_DIR)/*.o $(OUTPUT)

run: all
	@./$(OUTPUT)


check_automatically:
	@while true; do errors=$$(make check | grep -E ".[ch]pp:[0-9]+:[0-9]+");  numberOfWords=$$(echo $$errors | wc -w); clear; [ $$numberOfWords -gt 0 ]  && echo -e "\033[31mERROR\033[0m" || (echo -e "\033[32mALL OK\033[0m" && make run); echo "$$errors" | awk '{printf "\033[33m%s\033[0m \033[36m%s\033[0m\n", $$1, substr($$0, length($$1)+2)}' ; sleep 6; done

check:
	$(CC) $(CFLAGS) $(LDFLAGS) -fsyntax-only $(MAIN) 2>&1 | grep -v "pragma once"
