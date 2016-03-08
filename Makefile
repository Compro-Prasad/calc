CC = g++

CFLAGS = -c -Wall -ansi -o

TARGET = calc

SRCDIR = src/
STACKDIR = $(SRCDIR)calc_stacks/
SOURCES = $(wildcard $(SRCDIR)*.cpp $(STACKDIR)*.cpp)

OBJDIR = $(SRCDIR)obj/
OBJECTS = $(addprefix $(OBJDIR), $(subst .cpp,.o,$(notdir $(SOURCES))))

INCLUDE = -I$(SRCDIR)include/

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@if [ ! -d src/obj ]; then mkdir src/obj; fi
	$(CC) $(CFLAGS) $@ $< $(INCLUDE)

$(OBJDIR)%.o: $(STACKDIR)%.cpp
	$(CC) $(CFLAGS) $@ $< $(INCLUDE)

.PHONY: clean cleanall
clean:
	-rm -f $(OBJECTS)

cleanall:
	@if [ -f $(TARGET) ]; then rm -f $(TARGET); else echo "Target already removed"; fi
	@if [ -d $(OBJDIR) ]; then rm -r $(OBJDIR); else echo "Objects already removed"; fi
