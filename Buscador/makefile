gcc=g++
cflags=-std=c++20 -Wall
target=Buscador.exe
test=test.exe
testTarget=Testes.exe

bld = ./bld/
src = ./src/
incld = ./incld/
lib = ./lib/


${target}: ${bld}Accio.o ${bld}main.o
	${gcc} ${cflags} ${bld}Accio.o ${bld}main.o -o ${target}

${testTarget}: ${bld}test.o ${bld}Accio.o
	${gcc} ${cflags} ${bld}Accio.o ${bld}test.o -o ${testTarget}


test: ${bld}test.o ${bld}Accio.o ${testTarget}
	${gcc} ${cflags} ${bld}Accio.o ${bld}test.o -o ${testTarget}

${bld}test.o: ${src}Accio_test.cpp ${lib}doctest.h
	${gcc} ${cflags} -I ${lib} -I ${incld} -c ${src}Accio_test.cpp  -o ${bld}test.o 

${bld}Accio.o: ${incld}Accio.h ${src}Accio.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}Accio.cpp -o ${bld}Accio.o

${bld}main.o: ${incld}Accio.h ${lib}doctest.h ${src}main.cpp
	${gcc} ${cflags} -I ./incld/ -c ${src}main.cpp -o ${bld}/main.o

${bld}doctest.o: ${lib}doctest.h
	${gcc} ${cflags} -I ./lib/ -c ${lib}doctest.h -o ${bld}doctest.o

run: ${target}
	./${target}

run_test: ${testTarget}
	./${testTarget}

clear:
	rm ${target} ${testTarget}

clear_all:
	rm -f ${bld}*o && make clear
