FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/
FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/darwin/
FLAGS+=-Wall -Werror

JAVAFILES := $(wildcard src/*/*.java)
CLASSFILES := $(wildcard bin/*/*.class)

all: java

java: $(JAVAFILES)
	javac -d 'bin/' $(JAVAFILES)

.PHONY: clean
clean:
	rm -rf bin/*

.PHONY: native
native:
	g++ $(FLAGS) -dynamiclib -o libpokerai.jnilib pokerai.jni.cpp
