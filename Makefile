CXX = g++
CXXFLAGS = -std=c++14 -MMD -Werror=vla
OBJECTS = 	biquadris.o \
			utilities/helpers1.o \
			libr/graphics/window.o \
			src/cell/cell.o \
			src/blocks/block.o src/blocks/block_heavy.o src/blocks/blockGeneric.o src/blocks/blockI.o src/blocks/blockJ.o src/blocks/blockL.o src/blocks/blockN.o src/blocks/blockO.o src/blocks/blockS.o src/blocks/blockT.o src/blocks/blockZ.o \
			src/textDisplay/textDisplay.o \
			src/graphicDisplay/graphicDisplay.o \
			src/levels/level0.o src/levels/level1.o src/levels/level2.o src/levels/level3.o src/levels/level4.o \
			src/board/board.o \
			src/commands/commands.o \
			src/query/player.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
