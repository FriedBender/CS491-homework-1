cc=gcc
CFLAGS=
DFLAGS= -Wall -g
PROGS = CS491-HW-1-Program

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $

clean:
	rm -f $(PROGS) *o ~* a.out