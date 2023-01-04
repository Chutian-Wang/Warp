CXX   = g++
CCFLAGS = -std=c++11 -O3 -Wall
LIBS  = -lSDL2 -lSDL2_image

CACHEDIR = temp

TESTS = test VecTest warp_math_test texture_test

# Objects directory, must be created before running make.
OBJS = 	$(CACHEDIR)/warp_math.o	\
		$(CACHEDIR)/Vec.o \
		$(CACHEDIR)/texture.o

.PHONY: clean

all: $(TESTS) $(OBJS)

%: src/tests/%.cpp $(OBJS)
	${CXX} $(CCFLAGS) -o test_exec/$@ $^ $(LIBS)

$(CACHEDIR)/%.o: src/%.cpp
	$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	rm -f test_exec/*
	rm -f $(CACHEDIR)/*
