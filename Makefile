BIN	=	crack

SRC	=	src/main.cpp				\
		src/ADigest.cpp				\
		src/DigestMD5.cpp			\
		src/Cracker.cpp				\
		src/AttackBruteforce.cpp	\
		src/AttackDictionary.cpp	\
		src/Logger.cpp				\
		src/Color.cpp
OBJ	=	$(SRC:.cpp=.o)

INC	=	-I include
LIB	=	-lcrypto

CXXFLAGS	=	-g -fopenmp -O3 -W -Wall -Wextra
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
