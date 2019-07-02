obj := $(patsubst %.cu,%.o,$(wildcard *.cu))
flags = -I.
target = libraytracing.so
all: $(target)
%.o: %.cu %.h
	nvcc -Xcompiler -fPIC -c -G -g -o $@  $< $(flags)
$(target): $(obj)
	echo $(obj)
	nvcc -shared -g -o $@ $^ 

.PHONY: clean test
clean:
	rm $(obj)
	rm $(target) 
