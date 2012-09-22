SOURCES := $(shell find src -iname '*.cpp' )
OBJECTS := $(SOURCES:.cpp=.o)
LFLAGS := -lboost_regex-mt
CFLAGS := 

ifeq ($(DEBUG),YES)
	CFLAGS += -DDEBUG
endif

TESTCASES := tyda_simple

all:	yad

yad:	$(OBJECTS)
	g++ $(OBJECTS) $(LFLAGS) $(CFLAGS) -o yad

.cpp.o:
	g++ $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) yad

.PHONY: tests
tests:	$(TESTCASES)

tyda_simple:
	./yad -t potatis
