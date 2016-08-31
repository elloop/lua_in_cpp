CXX       = clang++
INCLUDE   = -I../

FLAGS     = -fpic 
FLAGS     += -undefined dynamic_lookup

LIBOPTS   = -shared
# LIBOPTS   = -bundle

# LINK_OPTS = ""
# LINK_OPTS = -llua

test.so: test.o
	$(CXX) $(LIBOPTS) $(FLAGS) $(LINK_OPTS) -o $@ $^

test.o : test.cpp
	$(CXX) $(INCLUDE) -c $^

.PHONY : clean
clean:
		-rm *.so *.o
