SRCPPS =  ./Crypt.cpp \
	./Except.cpp \
	start.cpp \
	Converter.cpp \
	Generator.cpp \
	Log.cpp \
	Parser.cpp

SRCS = 
CXXFLAGS = -std=c++11 -fpic -I../
OBJS = $(SRCPPS:.cpp=.o) $(SRCS:.c=.o)

.PHONY: build default all clear clean

all: build
default: build


build: $(OBJS)
	$(CXX) $(OBJS) ../libdp.a -o test

clear:
	$(RM) $(OBJS) test

clean: clear
	echo Ok