M_DIR=Engine
M_SRCS=Actor.cpp HitBox.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
