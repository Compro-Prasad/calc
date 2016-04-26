CC = g++

CFLAGS = -c -g -Wall -ansi -o

TARGET = calc

INSTALL_DIR = /usr/local/bin

SRCDIR = src/
STACKDIR = $(SRCDIR)calc_stacks/
SOURCES = $(wildcard $(SRCDIR)*.cpp $(STACKDIR)*.cpp)

OBJDIR = $(SRCDIR)obj/
OBJECTS = $(addprefix $(OBJDIR), $(subst .cpp,.o,$(notdir $(SOURCES))))

INCLUDE = -I$(SRCDIR)include/

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	$(CC) $(CFLAGS) $@ $< $(INCLUDE)

$(OBJDIR)%.o: $(STACKDIR)%.cpp
	$(CC) $(CFLAGS) $@ $< $(INCLUDE)

.PHONY: clean cleanall install
clean:
	-rm -f $(OBJECTS)

cleanall:
	@if [ -f $(TARGET) ]; then rm -f $(TARGET); else echo "Target already removed"; fi
	@if [ -d $(OBJDIR) ]; then rm -r $(OBJDIR); else echo "Objects already removed"; fi

install:
	@if [ ! -w $(INSTALL_DIR) ]; then echo $(INSTALL_DIR) has no write permissions for $(USER).; fi
	@if [ "$(USER)" != "root" ]; then echo "$(USER) has no sudo rights. Try using \"sudo make install\" or\
	\nconsult your administrator."; fi
	@if [ ! -f $(TARGET) ]; then echo "$(TARGET) is not build yet. Use make to build the source first."; exit; fi
	@if [ "$(USER)" = "root" -o "$(USER)" = "$(SUDO_USER)" -o -w "$(INSTALL_DIR)" ]; then cp "$(TARGET)" "$(INSTALL_DIR)" && echo Successfully installed; fi
