target := $(patsubst %.cpp,%,$(wildcard *.cpp))
flags = -I..
all: $(target)
%: %.cpp
	g++ -o $@  $< $(flags)
.PHONY: clean
clean:
	rm $(target) -i
