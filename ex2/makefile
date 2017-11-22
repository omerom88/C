
# a makefile for ex2 with 2 files, CheckParenthesis and waredb

# compile CheckParenthesis.c and waredb.c
all: CheckParenthesis waredb
	
# compile CheckParenthesis.c
CheckParenthesis: CheckParenthesis.c
	gcc -Wall -Wextra CheckParenthesis.c -o CheckParenthesis
	
# compile waredb.c
waredb: waredb.c
	gcc -Wall -Wextra waredb.c -o waredb
	
# clean files after finishing
clean:
	rm waredb CheckParenthesis
	
# phony files - clean isnt really a file but a command
.PHONY: clean