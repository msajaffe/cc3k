CXX=g++
XXFLAGS=-Wall -MMD
EXEC=cc3k
OBJECTS=cc3k.o textdisplay.o entity.o character.o item.o potion.o treasure.o player.o enemy.o floor.o chamber.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm ${OBJECTS}${EXEC}
	