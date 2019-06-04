SRCPPS =  ./Finder.cpp \
	main.cpp

SRCS = 
CXXFLAGS = -std=c++11 -fpic -I../../
OBJS = $(SRCPPS:.cpp=.o) $(SRCS:.c=.o)

.PHONY: build default all clear clean

all: build
default: build


build: $(OBJS)
	$(CXX) $(OBJS) ../../libdp.a -o OVPN

clear:
	$(RM) $(OBJS) OVPN

clean: clear
	echo Ok
