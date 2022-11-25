gcc=g++
cflags=-std=c++20 -Wall
target=Buscador.exe
test=test.exe

bld = ./bld/
src = ./src/
incld = ./incld/
lib = ./lib/


${bld}/target: ${bld}Accio.o ${bld}main.o
	${gcc} ${cflags} ${bld}*.o -o ${target}

test: ${src}Accio_test.cpp ${bld}Accio.o ${lib}doctest.h
	${gcc} ${cflags} ${src}Accio_test.cpp -I ${lib} ${lib}doctest.h ${bld}Accio.o -o ${test} 

${bld}Accio.o: ${incld}Accio.h ${src}Accio.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}Accio.cpp -o ${bld}Accio.o

${bld}main.o: ${incld}Accio.h ${lib}doctest.h ${src}main.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}main.cpp -o ${bld}/main.o

${bld}doctest.o: ${lib}doctest.h
	${gcc} ${cflags} -I ./lib/ -c ${lib}doctest.h -o ${bld}doctest.o

clear:
	rm ${target}

clear_all:
	rm -f ${bld}*o test.exe && make clear
