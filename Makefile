SRCPPS =  ./Log/stlog.cpp \
	./Crypt/SCH/System.cpp \
	./Crypt/SCH/v1/Crypt_v1.cpp \
	./Crypt/SCH/v1/Key_v1.cpp \
	./Crypt/SCH/v1/UniKey_v1.cpp \
	./Crypt/Converters/PrimitiveConverter.cpp \
	./Crypt/Crypt.cpp \
	version.cpp \
	Parser/ArgumentParser.cpp \
	Parser/SmartParser.cpp \
	Parser/Smart/Params.cpp \
	Parser/Smart/Symbol.cpp \
	Parser/Setting.cpp \
	Types/MemoryManager.cpp \
	Converter/Converter.cpp
SRCS = 
CXXFLAGS = -std=c++11 -fpic
OBJS = $(SRCPPS:.cpp=.o) $(SRCS:.c=.o)

.PHONY: build default all clear clean install_local

all: build
default: build


build: $(OBJS)
	$(AR) rc libdp.a $(OBJS)

clear:
	$(RM) $(OBJS) version.cpp

clean: clear
	echo Ok

install_local: clear
	$(RM) $(SRCPPS)
	$(RM) Crypt/iConverter.h
	$(RM) Crypt/iKeyGen.h
	$(RM) Crypt/SCH/System.h
	$(RM) Crypt/SCH/v1/Crypt_v1.h
	$(RM) Crypt/SCH/v1/UniKey_v1.h
	$(RM) Crypt/SCH/v1/Key_v1.h
	$(RM) -rf Crypt/SCH/v1
	$(RM) -f Crypt/Converters/PrimitiveConverter.h
	$(RM) -rf Crypt/Converters
	$(RM) -rf Crypt/SCH
	$(RM) -rf Example
	$(RM) -rf Debug
	$(RM) Makefile
	$(RM) init_example.sh
	$(RM) -rf TEST