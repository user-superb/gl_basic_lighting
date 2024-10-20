# makefile
PROJECT:= executable 
EXT:=

SRC_DIR:= src
OBJ_DIR:= obj
OUTPUT_DIR:= build

OUTPUT:= $(OUTPUT_DIR)/$(PROJECT)

INCLUDE_DIR:= -Iinclude
LIBS:= -lglfw3 -lGLU -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRC:= $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
OBJ:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)))
DEPS:= $(patsubst %.o,%.d,$(OBJ))

.PHONY:= clean

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	g++ $(OBJ) -o $@ $(LIBS)

-include $(DEPS)
 
#.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	g++ -MMD -c $< -o $@ $(INCLUDE_DIR)
#.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -MMD -c $< -o $@ $(INCLUDE_DIR)

clean:
	rm -r $(OUTPUT) $(OBJ_DIR)/*
