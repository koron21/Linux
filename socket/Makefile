#===========================================================================
# General Option
#=============================================================================

OUTDIR = ./bin
ifdef LLVM
CC = llvm-gcc
else
CC = gcc
endif
INCLUDE = -Iinclude
LIB = -Llib

#===========================================================================
# General Option
#=============================================================================

EXECUTABLE = server client
OBJECT = server.o client.o

#=============================================================================
# Flags, Definitions
#=============================================================================

CFLAG = -c -Wall
ifdef DEBUG
CFLAG += -O0 -ggdb3
else
CFLAG += -O3
endif

LDFLAG =

#=============================================================================
# Rules
#=============================================================================

all: $(EXECUTABLE)

client : client.o

server : server.o

.c.o:
	$(CC) $(INCLUDE) $(CFLAG) $(DEFINITIOINS) $< -o $@ $(LDFLAG)

clean:
	rm -rf $(OBJECT) $(EXECUTABLE) $(OUTDIR) $(SLIB) $(DLIB)

rebuild:
	make clean
	make

install:
	@if ! [ -d $(OUTDIR) ]; \
		then echo "making directory $(OUTDIR) for binary files" &&\
		mkdir $(OUTDIR); \
		fi
	mv $(OBJECT) $(EXECUTABLE) $(OUTDIR)

lib: $(OBJECT)
	$(AR) $(ARFLAGS) $(SLIB) $(OBJECT)
