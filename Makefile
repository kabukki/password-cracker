BIN	=	crack

SRC	=	src/main.cpp				\
		src/Cracker.cpp				\
		src/AttackBruteforce.cpp	\
		src/AttackDictionary.cpp	\
		src/Hash.cpp				\
		src/Logger.cpp				\
		src/Color.cpp
OBJ	=	$(SRC:.cpp=.o)

INC	=	-I include
LIB	=	-lcrypto

CXXFLAGS	=	-g -fopenmp -W -O3
CC			=	g++ $(CXXFLAGS)
RM			=	rm -rf

# Linking
$(BIN):	$(OBJ)
	$(CC) $^ $(INC) $(LIB) -o $@

# Compilation
%.o:	%.cpp
	$(CC) -c $< $(INC) -o $@

# Extra rules
all:	$(BIN)

clean:
	$(RM) $(OBJ)
fclean:	clean
	$(RM) $(BIN)
re: fclean all

.PHONY:	$(BIN)
