Configuration ?= Debug

Output = $(Configuration)/EndTermProject
Sources = main.c Evaluate.c Lexer.c LinkedList.c Misc.c Parser.c VariableTable.c
Options = -Wall

ifeq ($(Configuration),Debug)
Options += -DDEBUG -g
else
Options += -DNDEBUG
endif

all: prepare $(Output) Makefile

prepare:
	mkdir -p $(Configuration)

clean:
	rm -rf $(Configuration)

$(Output): $(Sources)
	$(CC) $(Options) -o $@ $^

# DEPENDENCIES
main.c: Evaluate.h Lexer.h Misc.h Parser.h VariableTable.h
Evaluate.c: Evaluate.h VariableTable.h
Evaluate.h: Expression.h
Lexer.c: Lexer.h
LinkedList.c: LinkedList.h
Misc.c: Misc.h
Misc.h: Expression.h
Parser.c: Parser.h
Parser.h: Expression.h Lexer.h
VariableTable.c: VariableTable.h LinkedList.h
