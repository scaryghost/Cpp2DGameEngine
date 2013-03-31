M_DIR=Core
M_SRCS=Object.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
