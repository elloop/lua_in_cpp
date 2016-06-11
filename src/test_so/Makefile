INCLUDE   = -I../
LIBOPTS   = -shared
FLAGS     = -fpic
CXX       = clang++
LINK_OPTS = -llua

test.so: test.o
	$(CXX) -bundle $(FLAGS) -L . $(LINKDIR) $(LINK_OPTS) -o $@ $^
	#$(CXX) -bundle $^ $(INCLUDE) $(FLAGS) $(LIBOPTS) $(LINKDIR) $(LINK_OPTS) -o $@

test.o : test.cpp
	$(CXX) $(INCLUDE) -c $^


