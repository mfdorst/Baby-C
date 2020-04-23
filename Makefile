CC = gcc
CFLAGS = -Wall -Wextra
SRCDIR = src
GENDIR = gen
OBJS := ast.o code_gen.o lexer.yy.o main.o parser.tab.o symbol_table.o util.o
EXE = bcc

#
# Debug build settings
#
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCFLAGS = -g -O0 -DDEBUG

#
# Release build settings
#
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake

# Default build
all: prep release

#
# Debug rules
#
debug: $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(GENDIR)/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#
# Release rules
#
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CC) $(CFLAGS) $(RELCFLAGS) -o $(RELEXE) $^

$(RELDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(GENDIR)/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

#
# Flex and Bison rules
#
$(GENDIR)/lexer.yy.c: $(SRCDIR)/lexer.l | $(GENDIR)/parser.tab.c
	flex -o $@ $<

$(GENDIR)/parser.tab.c: $(SRCDIR)/parser.y | $(GENDIR)
	bison -o $@ -d $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR) $(GENDIR)

remake: clean all

clean:
	rm -f $(RELEXE) $(RELOBJS) $(DBGEXE) $(DBGOBJS)
