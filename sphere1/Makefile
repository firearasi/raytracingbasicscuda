target := $(patsubst %.cu,%,$(wildcard *.cu))
flags = -g -G -I../lib  
all: $(target)
%: %.cu
	nvcc -o $@  $< $(flags)
.PHONY: clean test
clean:
	rm $(target) -i
test: $(target)
	./$(target) > pic.ppm
