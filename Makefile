CC = gcc
CFLAGS = -Wall -IC:\raylib\raylib\src
LDFLAGS = -LC:\raylib\raylib\src -mwindows -lraylib -lwinmm
SRC = $(wildcard challenge10.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

EXEC = challenge10.exe
RM = del

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)
