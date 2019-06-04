target := $(patsubst %.cpp,%,$(wildcard *.cpp))
flags = -I..
all: $(target)
%: %.cpp
	g++ -o $@  $< $(flags)
.PHONY: clean test
clean:
	rm $(target) -i
test: $(target)
	time ./$(target) > pic.ppm
	okular pic.ppm
