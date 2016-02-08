SOURCE = main.cpp \
         tokenize.cpp \
         hash.cpp
OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11 -c
CXXFLAGS = $(CFLAGS)



.PHONY: clean

# Targets include all, clean, debug, tar

all : zipf

zipf: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core zipf

debug: CXXFLAGS += -DDEBUG -g
debug: zipf

tar:
	tar cvf zipf_Tarball.tar *.cpp *.h Makefile

help:
	@echo "	make zipf  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core zipf"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; /usr/bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

