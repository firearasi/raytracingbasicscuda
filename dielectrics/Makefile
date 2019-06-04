target := $(patsubst %.cpp,%,$(wildcard *.cpp))
flags = -I..
all: $(target)
%: %.cpp
	g++ -g -o $@  $< $(flags)
.PHONY: clean test
clean:
	rm $(target) 
test: $(target)
	date
	time ./$(target) > pic.ppm
	date
	okular pic.ppm
