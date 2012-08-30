SOURCES := $(shell find src -iname '*.cpp' )
OBJECTS := $(SOURCES:.cpp=.o)
LFLAGS := -lboost_regex-mt

TESTCASES := tyda_simple

all:	yad

yad:	$(OBJECTS)
	g++ $(OBJECTS) $(LFLAGS) -o yad

.PHONY: clean
clean:
	rm $(OBJECTS) yad

.PHONY: tests
tests:	$(TESTCASES)

tyda_simple:
	./yad -t potatis
