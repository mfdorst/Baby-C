CXX = g++
CWARN = -Wall -Wextra -fsanitize=address
DBGCFLAGS = -g -O0

all: bbc

bbc: BabyC.tab.o BabyC.yy.o your_code.o driver.o 
	$(CXX) $(CWARN) $(DBGCFLAGS) BabyC.tab.o BabyC.yy.o driver.o your_code.o -o bcc

%.o: %.cpp
	$(CXX) $(CWARN) $(DBGCFLAGS) -c $<

%.yy.cpp: %.l
	flex -o $@ $<

%.tab.cpp: %.y
	bison -o $@ -d $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc
