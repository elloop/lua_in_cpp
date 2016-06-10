INCLUDE = -I../
LIBOPTS = -shared
FLAGS   = -fpic
CXX     = g++
LINK_OPTS = -llua


test.so: test.cpp
	$(CXX) $^ $(INCLUDE) $(FLAGS) $(LIBOPTS) $(LINKDIR) $(LINK_OPTS) -o $@

