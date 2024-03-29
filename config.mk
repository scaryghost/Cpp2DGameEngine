CPPC=g++
DIST=dist
LIB:=libcpp2dgameengine
MODULES=Core Engine

CPP_FLAGS:=-std=c++0x -Werror -Wall

ifdef DEBUG
    CPP_FLAGS+= -g
    LIB:=$(LIB)_debug.a
else
    LIB:=$(LIB).a
endif

ifeq ($(32BIT), 1)
	CPP_FLAGS+= -m32
endif
