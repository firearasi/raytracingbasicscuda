target := $(patsubst %.cu,%,$(wildcard *.cu))
flags = -g -G -I../lib -L../lib -lraytracing
all: $(target)
%: %.cu
	nvcc $(flags) -o $@  $< 
.PHONY: clean test
clean:
	rm $(target) -i
test: $(target)
	./$(target) > pic.ppm
	okular pic.ppm
