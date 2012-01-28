OBJECTS=gaussian.o
SOURCES=constants.h gaussian.cpp
MYPROGRAM=TrueSkill
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(OBJECTS)
	$(CC) -o $(MYPROGRAM) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) -c  $(SOURCES)
clean: 
	rm -f $(OBJECTS) $(MYPROGRAM)
