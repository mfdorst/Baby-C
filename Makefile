CC = gcc
WARNFLAGS = -Wall -Wextra
DEBUGFLAGS = -g -O0
OBJDIR = obj
SRCDIR = src
GENDIR = gen
OBJS := $(addprefix $(OBJDIR)/,ast.o code_gen.o lexer.yy.o main.o parser.tab.o symbol_table.o util.o)

all: bcc

bcc: $(OBJS)
	$(CC) $(WARNFLAGS) $(DEBUGFLAGS) $(OBJS) -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(WARNFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(GENDIR)/%.c
	$(CC) $(WARNFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(GENDIR)/lexer.yy.c: $(SRCDIR)/lexer.l | $(GENDIR)/parser.tab.c
	flex -o $@ $<

$(GENDIR)/parser.tab.c: $(SRCDIR)/parser.y | $(GENDIR)
	bison -o $@ -d $<

$(OBJDIR):
	mkdir $(OBJDIR)

$(GENDIR):
	mkdir $(GENDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(GENDIR)
	rm bcc
