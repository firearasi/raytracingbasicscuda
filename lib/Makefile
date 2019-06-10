obj := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
flags = -I.
target = libraytracing.so
all: $(target)
%.o: %.cpp %.h
	g++ -c -fPIC -g -o $@  $< $(flags)
$(target): $(obj)
	echo $(obj)
	g++ -shared -g -o $@ $^ 

.PHONY: clean test
clean:
	rm $(obj)
	rm $(target) 
