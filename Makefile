SRC_DIR= src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = ${wildcard ${SRC_DIR}/*.cpp} ${wildcard ${SRC_DIR}/cpu/*.cpp}
OBJ_NAME = legendarytrain
LIBRARY_PATHS = -lSDL2
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g

all:
	${CC} ${COMPILER_FLAGS} ${LIBRARY_PATHS} ${SRC_FILES} -o ${BUILD_DIR}/${OBJ_NAME}

run: 
	./${BUILD_DIR}/${OBJ_NAME}

clean: 
	rm -rf ${BUILD_DIR}/*
