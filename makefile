CXX = g++
CXXFLAGS = -std=c++17 -w -Wextra -pedantic -O3 -Wall

LDFLAGS = 

SRCS = shor.cpp

OBJS = $(addprefix obj/,$(SRCS:.cpp=.o))

EXEC = shor

all: obj $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

obj/%.o: %.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f $(OBJS) $(EXEC)
	rmdir obj