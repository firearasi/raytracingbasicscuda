target := $(patsubst %.cpp,%,$(wildcard *.cpp))
flags = -I.. -lpthread
all: $(target)
%: %.cpp
	g++ -g -o $@  $< $(flags)
.PHONY: clean test
clean:
	rm $(target) 
test: $(target)
	date
	time "./$(target)" 
	date
