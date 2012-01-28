OBJECTS= *.o 
REMOBJ= *.gch
SOURCES= *.h *.cpp
MYPROGRAM=TrueSkill
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(OBJECTS)
	$(CC) -o $(MYPROGRAM) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) -I. -c -w $(SOURCES)
clean: 
	rm -f $(OBJECTS) $(REMOBJ) $(MYPROGRAM)
