BIN	=	example
OBJS	=	libcavl.o main.o
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
	@$(CC) $(CFLAGS) -c $<

all: $(BIN)

$(BIN): $(OBJS)
	@echo "LD	$@";
	@$(CC) -o $@ $(OBJS)

clean:
	$(RM) -f $(BIN) $(OBJS)
