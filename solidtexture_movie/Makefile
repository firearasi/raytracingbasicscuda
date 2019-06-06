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
	ffmpeg -framerate 25 -i "movie/frame%03d.ppm" -start_number 0 movie/output.mpg
