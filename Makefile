# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/25 18:13:09 by sverschu      #+#    #+#                  #
#    Updated: 2020/08/25 18:14:12 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libexecblocks.a

# build variables

# directories
SRC_D = src
OBJ_D = obj
INC_D = inc

# C source and header files
SRC =	$(SRC_D)/execblocks.c												\

INC =	$(INC_D)/execblocks.h												\

OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

# output format
CC_LOG=./.cc.log
CC_ERROR=./.cc.error

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

# warriors of choice
ECHO=printf
CAT=cat

# compiler and linker
CC = clang
LD = ar

# compile, linker and test flags
CC_FLAGS =	-Wall -Wextra -Werror
LD_FLAGS =  -rcs
T_FLAGS = 	-lcriterion

# debugging or optimilization flags
CC_OPT_FLAGS = -O3															\
			   -march=native

ifeq ($(ASAN),1)
	CC_FLAGS += -fsanitize=address											\
				-fno-optimize-sibling-calls
	LD_FLAGS +=
	DEBUG = 1
endif

ifeq ($(DEBUG),1)
	CC_FLAGS += -g 															\
				-O0															\
				-fno-omit-frame-pointer										\
				-fstack-protector-all										\
				-DDEBUG
	LD_FLAGS +=
else
	CC_FLAGS += $(CC_OPT_FLAGS)
	LD_FLAGS +=
endif

# os variables
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    OS = LINUX
    CC_FLAGS += -D LINUX -Wno-misleading-indentation
    LD_FLAGS +=
endif
ifeq ($(UNAME_S),Darwin)
    OS = OSX
    CC_FLAGS += -D OSX
    LD_FLAGS +=
endif

# make commands
all: $(NAME)

submodule:
	@git submodule update --init --remote --recursive

$(NAME): $(OBJ_D) $(OBJ) $(INC_D) $(INC)
	@$(ECHO) "Linking $(NAME)..."
	@$(LD) $(LD_FLAGS) $(NAME) $(OBJ) 2>$(CC_LOG)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) -c $< -o $@ 2>$(CC_LOG) 					\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(NAME).dSYM
	@$(RM) *.testbin
	@$(RM) -r $(OBJ_D)

fclean: clean
	@$(RM) $(NAME)

norm:
	@norminette $(SRC) $(INC)

re: fclean all

basics_crit_test: TEST='basics_crit_t'
basics_crit_test: $(NAME)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) -I$(INC_D) -o $(TEST).testbin tests/$(TEST).c $(NAME) $(T_FLAGS)
	@if test -e $(CC_ERROR); then                                           \
        $(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
    elif test -s $(CC_LOG); then                                            \
        $(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);                     \
    else                                                                    \
        $(ECHO) "$(OK_STRING)\n";                                           \
    fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin $(CRIT_FLAGS) && $(RM) -f $(TEST).testbin && $(RM) -rf $(TEST).dSYM 2>$(CC_LOG)
	@# output removed; criterion is clear enough
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

tests: $(NAME)
	@make basics_crit_test

.PHONY = all clean fclean re
