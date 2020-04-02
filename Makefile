CXX = g++
CXXFLAGS = -std=c++11
WARNFLAGS = -Wall -Wextra -Wno-deprecated-register -fsanitize=address
DEBUGFLAGS = -g -O0

all: bcc

OBJS := parser.tab.o lexer.yy.o ast.o symbol_table.o main.o

bcc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(WARNFLAGS) $(DEBUGFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(WARNFLAGS) $(DEBUGFLAGS) -c $<

%.yy.cpp: %.l
	flex -o $@ $<

%.tab.cpp: %.y
	bison -o $@ -d $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc
