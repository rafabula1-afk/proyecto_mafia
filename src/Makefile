CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I./src
LDFLAGS = 


SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/mafia



all: directories $(EXECUTABLE)


directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)


$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Compilación completada: $(EXECUTABLE)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
	@echo "Limpieza completada"


run: all
	cd $(BIN_DIR) && ./mafia


rebuild: clean all

.PHONY: all clean run rebuild directories