SOURCES := $(shell find . -iname '*.cpp' )
OBJECTS := $(SOURCES:.cpp=.o)
LFLAGS := -lboost_regex-mt

all:	yad

yad:	$(OBJECTS)
	g++ $(OBJECTS) $(LFLAGS) -o yad

.PHONY: clean
clean:
	rm $(OBJECTS) yad
