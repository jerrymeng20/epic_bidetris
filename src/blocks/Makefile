CXX = g++
CXXFLAGS = -std=c++14 -MMD -Werror=vla -g
OBJECTS = 	unittest.o \
			../../utilities/helpers1.o \
			../cell/cell.o \
			block.o blockGeneric.o blockI.o blockJ.o blockL.o blockN.o blockO.o blockS.o blockT.o blockZ.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = unittest

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
