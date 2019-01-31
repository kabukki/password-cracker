BIN	=	crack

SRC	=	src/main.cpp

OBJ	=	$(SRC:.cpp=.o)

INC	=	-I include

CC			=	g++
CXXFLAGS	=	-g $(INC)
RM			=	rm -rf

all:	$(BIN)

$(BIN):	$(OBJ)
	$(CC) $(OBJ) -o $(BIN)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BIN)

re: fclean all

.PHONY:	$(BIN)
