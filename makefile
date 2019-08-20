CC = g++
CFLAGS = -g -Wall
OBJS = test_editor.o textEditor.o 

EXEC = MS


all: $(SRCS) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o MS 

test_editor.o: test_editor.cpp
	$(CC) -c test_editor.cpp

textEditor.o: textEditor.h textEditor.cpp
	$(CC) -c textEditor.cpp

