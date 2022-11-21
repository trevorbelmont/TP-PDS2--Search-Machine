gcc=g++
cflags=-std=c++20 -Wall
target=Accio_Buscador.exe

bld = ./bld/
src = ./src/
incld = ./incld/
lib = ./lib/


${bld}/target: ${bld}Accio.o ${bld}main.o
	${gcc} ${cflags} ${bld}*.o -o ${target}

${bld}Accio.o: ${incld}Accio.h ${src}Accio.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}Accio.cpp -o ${bld}Accio.o

${bld}doctest.o: ${lib}doctest.h
	${gcc} ${cflags} -I ./lib/ -c ${lib}doctest.h -o ${bld}doctest.o

${bld}main.o: ${incld}Accio.h ${lib}doctest.h ${src}main.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}main.cpp -o ${bld}/main.o

clear:
	rm ${target}

clear_all:
	rm -f ${bld}*o && make clear
