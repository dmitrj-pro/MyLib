#!/bin/bash


#(((find -iname '*.cpp' | xargs echo -e 'SRCPPS = ') && (find -iname '*.c' | xargs echo -e 'SRCS = ')) && echo -e 'OBJS = $(SRCPPS:.cpp=.o) $(SRCS:.c=.o)\n\nEXEC = hello\n$(EXEC): $(OBJS)\n\t$(CC) $(OBJS) -o $@\nall: $(EXEC)') > proj.pro


(echo -e "QT\t-= core gui" && echo "TARGET = Project" && echo "CONFIG += c++11" \
	&& (find -iname '*.cpp' | xargs echo -e "SOURCES += \\ \n\t") \
	&& (find -iname '*.h' | xargs echo -e "HEADERS += \\ \n\t") \
	) > Proj.pro

