# Makefile #

# Gabriel A S #
# Mayra D A #


## DIRS
INCDIR = include
SRCDIR = src
OBJDIR = build

# TARGET
TARGET = $(OBJDIR)/bin

## EXTENSIONS
SRCEXT = cpp

## SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

## OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

## COMPILER
CC = g++

## FLAGS
WARN = -Wall
INCFLAG = -I $(INCDIR)
CFLAGS = $(WARN) -std=c++11 $(INCFLAG) -c

all: $(TARGET) clean	
	
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Gerando código objeto..."
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET): $(OBJS)
	@echo "Compilando..."
	$(CC) $^ $(INLFLAG) $(LIBFLAG) -o $@  

.PHONY: clean
clean:
	@echo "Limpando..."
	@rm -rf $(OBJDIR)/*.o