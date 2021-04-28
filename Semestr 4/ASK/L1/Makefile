COMPILER = g++
COMPILER_FLAGS = \
	-xc \
	-std=c11 \
	-Wall \
	-Werror \
	-Wextra \
	-pedantic \
	-Wpedantic \
	-Wfloat-equal \
	-Wundef \
	-Wshadow \
	-Wpointer-arith \
	-Wcast-align \
	-Wstrict-overflow=5 \
	-Wwrite-strings \
	-Wcast-qual \
	-Wswitch-default \
	-Wswitch-enum \
	-Wconversion \
	-Wunreachable-code \
	-ftrapv \
	-fverbose-asm \
	-finstrument-functions \
	-finline-functions \
	-ftree-vectorize \
	-funroll-loops \
	-Os \
	-Wno-unused-parameter
OUTPUT_NAME = binary
SOURCE = *.c
LIBRARIES = \
	-lm
FLAGS = \
	-Ddebug_flag

default: all

all:
	${COMPILER} ${COMPILER_FLAGS} -o ${OUTPUT_NAME} ${SOURCE} ${LIBRARIES} ${FLAGS}