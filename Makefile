CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -D_POSIX_C_SOURCE=200112L
LIBS=-lpthread

ODIR=obj
BDIR=bin
SDIR=src

_OBJ = main.o tp1/queue_and_stack_operations.o tp2/archiver.o tp2/unarchiver.o tp3/ls.o tp4_5/shell.o tp4_5/ligne_commande.o test/no_ram_for_you.o tp6/encoder.o tp6/decoder.o tp6/modif_bmp.o ctp/minuscule.o ctp/filtre.o ctp/processus.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/r305: $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

all: $(BDIR)/r305

run: $(BDIR)/r305
	./$(BDIR)/r305

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)