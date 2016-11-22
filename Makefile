FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/
FLAGS+=-I /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/include/darwin/
FLAGS+=-Wall -Werror

.PHONY: native
native:
	g++ $(FLAGS) -dynamiclib -o libpokerai.jnilib pokerai.jni.cpp
