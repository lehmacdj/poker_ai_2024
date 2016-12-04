# FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/
# FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/darwin/
FLAGS+=-Wall
FLAGS+=-std=c++11

JAVAFILES := $(wildcard src/*/*.java)
CLASSFILES := $(wildcard bin/*/*.class)

all: native java

java: $(JAVAFILES)
	javac -d 'bin/' $(JAVAFILES)

.PHONY: clean
clean:
	rm -rf bin/*

SOURCES=PokerBot/Board.cpp PokerBot/Card.cpp PokerBot/Hand.cpp PokerBot/Hole.cpp PokerBot/Range.cpp PokerBot/main.cpp PokerBot/PokerLib.cpp

.PHONY: native
native:
	g++ $(FLAGS) -dynamiclib -o lib/libPoker.jnilib $(SOURCES)
