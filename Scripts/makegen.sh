#!/bin/bash


(((find -iname '*.cpp' | xargs echo -e 'SRCPPS = ') && (find -iname '*.c' | xargs echo -e 'SRCS = ')) && echo -e 'OBJS = $(SRCPPS:.cpp=.o) $(SRCS:.c=.o)\n\nEXEC = hello\n$(EXEC): $(OBJS)\n\t$(CC) $(OBJS) -o $@\nall: $(EXEC)') > Makefile
