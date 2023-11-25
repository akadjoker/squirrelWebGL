NAME = libsquirrel
TARGET = $(NAME).a

UNAMEOS = $(shell uname)
ifeq ($(OS),Windows_NT)
    RM = del /Q
else ifeq ($(UNAMEOS),Linux)
    RM = rm -f
endif

SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

HEAD = -Isrc -Iinclude
CC   =  g++
#CFLAGS =  -O2 -fno-exceptions -fno-rtti  -fno-strict-aliasing 
CFLAGS = $(HEAD) -O2 -m64 -D_SQ64 -DDISABLE_DYNAMIC -DSTATIC -fno-exceptions -fno-rtti  -fno-strict-aliasing 

ifeq ($(UNAMEOS),Linux)
    LDFLAGS += 
endif

ifeq ($(OS),Windows_NT)
    LDFLAGS +=  
endif


$(TARGET): $(OBJS)
	ar -r -s $(TARGET) $(OBJS)

 

	


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(TARGET)


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all  clean fclean re
