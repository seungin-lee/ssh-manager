CPP = g++
INCLUDE_DIR += include
CFLAGS = -I$(INCLUDE_DIR) -g
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = ssh-manager

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CPP) -o $@ $^
%.o : %.cpp
	$(CPP) $(CFLAGS) -c $^ -o $@

clean :
	rm -f $(OBJS) $(TARGET)
