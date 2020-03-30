CXX = g++
CWARN = -Wall -Wextra -fsanitize=address
DBGCFLAGS = -g -O0

all: bcc

OBJS := parser.tab.o lexer.yy.o ast.o main.o

bcc: $(OBJS)
	$(CXX) $(CWARN) $(DBGCFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CWARN) $(DBGCFLAGS) -c $<

%.yy.cpp: %.l
	flex -o $@ $<

%.tab.cpp: %.y
	bison -o $@ -d $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc
