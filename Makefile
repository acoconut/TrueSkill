OBJECTS= *.o *.gch
SOURCES= *.h *.cpp
MYPROGRAM=TrueSkill
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(OBJECTS)
	$(CC) -o $(MYPROGRAM) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) -c  $(SOURCES)
clean: 
	rm -f $(OBJECTS) $(MYPROGRAM)
