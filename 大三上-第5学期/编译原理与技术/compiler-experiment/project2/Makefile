CC=gcc

GPP = g++
FLEX = flex
BISON = bison
CXX_STD = -std=c++17

CXX_DEBUG = -g -Wall
SRC_PATH = codes
CXX_WARN = -Wall -Wextra
MAKE_PATH = ./make-build-dir
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN)
CPP = $(GPP) $(CXX_FLAGS)

.PHONY: clean
.lex: $(SRC_PATH)/lex.l
	$(FLEX) -o $(SRC_PATH)/lex.yy.c $(SRC_PATH)/lex.l

.syntax: $(SRC_PATH)/syntax.y
		$(BISON) -Wno-conflicts-sr -t -d -v $(SRC_PATH)/syntax.y -o $(SRC_PATH)/syntax.tab.c

.node: .lex .syntax
	$(CPP) -c $(SRC_PATH)/node.cpp -o $(SRC_PATH)/node.o
	@ar -rc $(SRC_PATH)/libnode.a $(SRC_PATH)/node.o

.yyerror: .lex .syntax
	$(CPP) -c $(SRC_PATH)/error.cpp -o $(SRC_PATH)/error.o
	@ar -rc $(SRC_PATH)/liberror.a $(SRC_PATH)/error.o

.type: .lex .syntax
	$(CPP) -c $(SRC_PATH)/type.cpp -o $(SRC_PATH)/type.o
	@ar -rc $(SRC_PATH)/libtype.a $(SRC_PATH)/type.o

.semanticError: .lex .syntax
	$(CPP) -c $(SRC_PATH)/semantics.cpp -o $(SRC_PATH)/semantics.o
	@ar -rc $(SRC_PATH)/libsemantics.a $(SRC_PATH)/semantics.o

.visit: .lex .syntax
	$(CPP) -c $(SRC_PATH)/SyntaxTree.cpp -o $(SRC_PATH)/SyntaxTree.o
	@ar -rc $(SRC_PATH)/libSyntaxTree.a $(SRC_PATH)/SyntaxTree.o

bplc: .node .yyerror .type .semanticError .visit
	$(CPP) $(SRC_PATH)/main.cpp -static -L$(SRC_PATH) -lnode -lerror  \
    -lSyntaxTree -lsemantics -ltype  -o ./bin/bplc
clean:
	@rm -rf $(MAKE_PATH)/ $(SRC_PATH)/lex.yy.c $(SRC_PATH)/syntax.tab.* $(SRC_PATH)/*.out \
		$(SRC_PATH)/*.o $(SRC_PATH)/*.a $(SRC_PATH)/*.so $(SRC_PATH)/syntax.output 
.PHONY: bplc