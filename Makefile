CC = g++
CXX = $(CC)

CFLAGS = -O3 -Ofast -Wall -ansi -pedantic
CXXFLAGS = $(CFLAGS)
ALL_CFLAGS = $(CFLAGS) -c -o
ALL_CXXFLAGS = $(CXXFLAGS) -c -o

TARGET = calc

SRCDIR = src/
STACKDIR = $(SRCDIR)calc_stacks/
SOURCES = $(wildcard $(SRCDIR)*.cpp $(STACKDIR)*.cpp)

OBJDIR = $(SRCDIR)obj/
OBJECTS = $(addprefix $(OBJDIR), $(subst .cpp,.o,$(notdir $(SOURCES))))

INCLUDE = -I$(SRCDIR)include/

PREFIX=/usr/local/
INSTALL_PREFIX=$(PREFIX)

INSTALL_DIR = $(INSTALL_PREFIX)bin/

MANPATH=$(INSTALL_PREFIX)share/man/man1/
MANPAGE=doc/man/man1/$(TARGET).1

all: $(TARGET) doc

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	$(CXX) $(ALL_CXXFLAGS) $@ $< $(INCLUDE)

$(OBJDIR)%.o: $(STACKDIR)%.cpp
	$(CXX) $(ALL_CXXFLAGS) $@ $< $(INCLUDE)

.PHONY: clean cleanall install
clean:
	-rm -f $(OBJECTS)

cleanall:
	@if [ -f $(TARGET) ]; then rm -f $(TARGET); else echo "Target already removed"; fi
	@if [ -d $(OBJDIR) ]; then rm -r $(OBJDIR); else echo "Objects already removed"; fi

install:
	@cp "$(TARGET)" "$(INSTALL_DIR)" && echo Successfully installed;
	-mkdir -p $(MANPATH);
	@cp "$(MANPAGE)" "$(MANPATH)" && echo Man page made available;
