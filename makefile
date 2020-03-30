CC = gcc
CWARN = -Wall -Wextra -fsanitize=address
DBGCFLAGS = -g -O0

all: bbc

debug: bbc

bbc: Parser Scanner YourCode 
	$(CC) $(CWARN) $(DBGCFLAGS) BabyC.tab.o lex.yy.o driver.o your_code.o -o bcc

YourCode: your_code.o driver.o 

Scanner: BabyC.lex 
	flex BabyC.lex
	$(CC) $(DBGCFLAGS) -c lex.yy.c

Parser: BabyC.y  
	bison -d BabyC.y
	$(CC) $(DBGCFLAGS) -c BabyC.tab.c

%.o: %.c 
	$(CC) $(CWARN) $(DBGCFLAGS) -c $<

clean:
	rm -f *.o *.tab.* *.yy.* bcc
