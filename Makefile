CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/FechoConvexo.o $(OBJ)/Ponto.o $(OBJ)/Utils.o
HDRS = $(INC)/FechoConvexo.hpp $(INC)/Ponto.hpp $(INC)/Stack.hpp $(INC)/Utils.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
	$(EXE) -i points.in

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/FechoConvexo.o: $(HDRS) $(SRC)/FechoConvexo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/FechoConvexo.o $(SRC)/FechoConvexo.cpp

$(OBJ)/Ponto.o: $(HDRS) $(SRC)/Ponto.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Ponto.o $(SRC)/Ponto.cpp

$(OBJ)/Utils.o: $(HDRS) $(SRC)/Utils.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Utils.o $(SRC)/Utils.cpp
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out