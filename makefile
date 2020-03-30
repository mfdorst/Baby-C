CXX = g++
CWARN = -Wall -Wextra -fsanitize=address
DBGCFLAGS = -g -O0

all: bbc

debug: bbc

bbc: Parser Scanner YourCode 
	$(CXX) $(CWARN) $(DBGCFLAGS) BabyC.tab.o BabyC.yy.o driver.o your_code.o -o bcc

YourCode: your_code.o driver.o

Scanner: BabyC.lex 
	flex -o BabyC.yy.cpp BabyC.lex
	$(CXX) $(DBGCFLAGS) -c BabyC.yy.cpp

Parser: BabyC.y  
	bison -o BabyC.tab.cpp -d BabyC.y
	$(CXX) $(DBGCFLAGS) -c BabyC.tab.cpp

%.o: %.cpp
	$(CXX) $(CWARN) $(DBGCFLAGS) -c $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc
