# target source
include ../../../../Makefile.param
INCLUDES := $(INCLUDES) -I./include -I../ImageAlgo/include
#INCLUDES := $(INCLUDES) -I./include
VPATH+= src include
ORG := $(wildcard src/*.c)
SRC := $(subst src/,,$(ORG)) 
OBJ := $(SRC:%.c=%.o)
.PHONY : all clean list

all: $(OBJ)


%.o: %.c
	 $(CC) $(CFLAGS) -c $< $(INCLUDES) 

clean:
	@rm -f *.o
