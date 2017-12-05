Configuration ?= Debug

Output = $(Configuration)/EndTermProject
Sources = main.c LinkedList.c Lexer.c Parser.c VariableTable.c
Options = -Wall

ifeq ($(Configuration),Debug)
Options += -DDEBUG -g
else
Options += -DNDEBUG
endif

all: prepare $(Output)

prepare:
	mkdir -p $(Configuration)

clean:
	rm -rf $(Configuration)

$(Output): $(Sources)
	$(CC) -o $@ $^

# DEPENDENCIES
main.c: VariableTable.h Lexer.h Parser.h
LinkedList.c: LinkedList.h
Lexer.c: Lexer.h
Parser.c: Parser.h Lexer.h
VariableTable.c: VariableTable.h LinkedList.h