CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -Wextra -Werror

BIN=MarioLANG
INSTALL=mariolang
SRCS=src/main.cc src/level/level.cc src/mario/mario.cc src/memory-band/memory-band.cc
OBJS=$(subst .cc,.o,$(SRCS))

.PHONY: all install clean

all: ${BIN}

${BIN}: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${BIN} ${OBJS}

install: ${BIN}
	install ${BIN} /usr/local/bin/${INSTALL}

clean:
	${RM} ${BIN} ${OBJS}
