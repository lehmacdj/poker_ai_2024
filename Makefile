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

SOURCES=native/Board.cpp native/Card.cpp native/Hand.cpp native/Hole.cpp native/Range.cpp native/main.cpp native/PokerLib.cpp

.PHONY: native
native:
	g++ $(FLAGS) -dynamiclib -o lib/libPoker.jnilib $(SOURCES)
