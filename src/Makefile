# Compiler
CC = g++

# Include files
INCLUDE = .

# CFLAGS
CFLAGS = -c -Wall -ansi

# Objects
OBJECTS = main.o calc_cmd_action.o cal.o calc_file.o calc_history.o calc_help.o calc_strings.o calc_ans.o str.o calc_colors.o calc_constants.o

calc: $(OBJECTS)
	$(CC) -o calc $(OBJECTS)

main.o: calc_features.h calc_cmd_action.h
	$(CC) $(CFLAGS) main.cpp

calc_cmd_action.o: calc_cmd_action.cpp calc_constants.h cal.h calc_history.h calc_file.h calc_help.h
	$(CC) $(CFLAGS) calc_cmd_action.cpp

cal.o: cal.cpp str.h calc_colors.h calc_ans.h calc_strings.h
	$(CC) $(CFLAGS) cal.cpp

calc_history.o: calc_history.cpp calc_strings.h calc_features.h
	$(CC) $(CFLAGS) calc_history.cpp

calc_file.o: calc_file.cpp calc_features.h chatr.h
	$(CC) $(CFLAGS) calc_file.cpp

calc_help.o: calc_help.cpp calc_features.h
	$(CC) $(CFLAGS) calc_help.cpp

str.o: str.cpp chatr.h
	$(CC) $(CFLAGS) str.cpp

calc_constants.o: calc_constants.cpp calc_features.h
	$(CC) $(CFLAGS) calc_constants.cpp

calc_ans.o: calc_ans.cpp calc_colors.h calc_strings.h
	$(CC) $(CFLAGS) calc_ans.cpp

calc_strings.o: calc_strings.cpp chatr.h
	$(CC) $(CFLAGS) calc_strings.cpp

calc_colors.o: calc_colors.cpp calc_features.h
	$(CC) $(CFLAGS) calc_colors.cpp

.PHONY: clean
clean:
	-rm -f $(OBJECTS)
