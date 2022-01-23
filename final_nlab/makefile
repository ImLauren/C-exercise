CC := clang

CWARNS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99 -Werror

SANITIZE := $(CWARNS) -fsanitize=address -fsanitize=undefined -g3


# 'make all' builds production and sanitize exectuables
all : parse testparse interp testinterp extension


# 'make parse' builds a program that can detect syntax (Manual writer file name required)
parse: Parse/parse.c  Parse/parsemain.c
	$(CC) Parse/parse.c  Parse/parsemain.c  $(SANITIZE) -o parse -lm
# 'make testparse' builds a program that can test parse
testparse: Parse/parse.c Parse/testparse.c
	$(CC) Parse/parse.c  Parse/testparse.c $(SANITIZE) -o testparse -lm

# 'make interp' builds a program that can execute programs
interp: Interpreter/interp.c  Interpreter/interpmain.c
	$(CC) Interpreter/interp.c  Interpreter/interpmain.c  $(SANITIZE) -o interp -lm
# 'make testinterp' builds a program that can test interp
testinterp: Interpreter/interp.c Interpreter/testinterp.c
	$(CC) Interpreter/interp.c  Interpreter/testinterp.c $(SANITIZE) -o testinterp -lm

# 'make extension' builds a program that can execute programs
extension: Extension/extension.c  Extension/extenmain.c
	$(CC) Extension/extension.c  Extension/extenmain.c  $(SANITIZE) -o extension -lm


# 'make clean' removes all executables
clean: 
	rm -f parse testparse interp testinterp extension
