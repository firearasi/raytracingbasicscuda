target := $(patsubst %.cpp,%,$(wildcard *.cpp))
flags = -I.. -lpthread
all: $(target)
%: %.cpp
	g++ -o $@  $< $(flags)
.PHONY: clean test
clean:
	rm $(target) -i
test: $(target)
	date
	time ./$(target) > pic.ppm
	date
	okular pic.ppm
