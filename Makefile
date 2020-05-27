CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -Wextra -Werror

BIN=MarioLANG
INSTALL_NAME=mariolang
DEP=src/main.c

.PHONY: all install clean

all: ${BIN}

${BIN}: ${DEP}
	${CXX} ${CXXFLAGS} -o ${BIN} ${DEP}

install: ${BIN}
	install ${BIN} /usr/local/bin/${INSTALL_NAME}

clean:
	${RM} ${BIN}
