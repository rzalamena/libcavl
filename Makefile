BIN	=	example
BINALT	=	example_alt
OBJS	=	libcavl.o
RM	=	rm
CC	=	gcc
CFLAGS	+=	-Wall
CFLAGS	+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+=	-Wmissing-declarations -Wshadow
CFLAGS	+=	-Wpointer-arith -Wcast-qual
CFLAGS	+=	-Wsign-compare

.PHONY: clean

.c.o:
	@echo "CC	$<";
	@$(CC) $(CFLAGS) -c $<;

all: $(BIN) $(BINALT)

$(BIN): $(OBJS)
	@echo "CC	main.c";
	@$(CC) -c main.c;
	@echo "LD	$@";
	@$(CC) -o $@ $(OBJS) main.o;

$(BINALT): $(OBJS)
	@echo "CC	strings.c";
	@$(CC) -c strings.c;
	@echo "LD	$@";
	@$(CC) -o $@ $(OBJS) strings.o;

clean:
	$(RM) -f $(BIN) $(BIN).core main.o $(BINALT) $(BINALT).core strings.o cscope.out $(OBJS);
