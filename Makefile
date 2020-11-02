# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/25 18:13:09 by sverschu      #+#    #+#                  #
#    Updated: 2020/10/25 22:48:32 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME				= libexectree.a

# internal libraries ########################################################
COMMON          	= common.a
TREE				= node.a
LOGGER				= logger.a
GRAMMARGENERATOR	= lexergenerator.a
LEXER				= lexer.a
PARSER				= parser.a
ALLDEPS         	= $(COMMON) $(TREE) $(LOGGER) $(GRAMMARGENERATOR) $(LEXER) $(PARSER)

# directories ###############################################################
SRC_D 				= src
OBJ_D 				= obj
INC_D 				= inc
LIB_D 				= lib

# common source files #######################################################
SRC =	$(SRC_D)/common/exectree_lifetime.c									\
		$(SRC_D)/common/exectree_parse.c									\

OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

# tree source files #########################################################
TREE_SRC =	$(SRC_D)/tree/node_lifetime.c									\
			$(SRC_D)/tree/tree_lifetime.c									\

TREE_OBJ :=	$(TREE_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### logger source files
LOG_SRC=	$(SRC_D)/logger/logger.c										\

LOG_OBJ :=	$(LOG_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### grammar generator source files
GG_SRC =	$(SRC_D)/grammargenerator/grammar_ir.c							\
			$(SRC_D)/grammargenerator/grammar_ir_lifetime.c					\
			$(SRC_D)/grammargenerator/gg_process_production.c				\
			$(SRC_D)/grammargenerator/gg_process_rules.c					\
			$(SRC_D)/grammargenerator/gg_process_nonterminal.c				\
			$(SRC_D)/grammargenerator/gg_process_word.c						\
			$(SRC_D)/grammargenerator/gg_process_literal.c					\
			$(SRC_D)/grammargenerator/gg_rule_lifetime.c					\
			$(SRC_D)/grammargenerator/gg_production_lifetime.c				\
			$(SRC_D)/grammargenerator/gg_token_lifetime.c					\
			$(SRC_D)/grammargenerator/gg_dump.c								\
			$(SRC_D)/grammargenerator/gg_search.c							\
			$(SRC_D)/grammargenerator/gg_post_processing.c					\
			$(SRC_D)/grammargenerator/gg_jumptable.c						\

GG_OBJ :=	$(GG_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### lexer source files
LEX_SRC =	$(SRC_D)/lexer/lexer.c											\

LEX_OBJ :=	$(LEX_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### parser source files
PARSE_SRC =		$(SRC_D)/parser/parser.c									\

PARSE_OBJ :=	$(PARSE_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

# dependencies ##############################################################
LIBGNL=lib/libgnl/libgnl.a
LIBFT=lib/libft/libft.a
LIBVECTOR=lib/libvector/libvector.a
LIB_INC= -I$(LIB_D)/libgnl/inc												\
		 -I$(LIB_D)/libft/inc												\
		 -I$(LIB_D)/libvector/inc											\

# output format #############################################################
CC_LOG=./.cc.log
CC_ERROR=./.cc.error

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

# warriors of choice ########################################################
ECHO=printf
CAT=cat

# compiler and linker #######################################################
CC = clang
LD = ar
LT = libtool

# compile, linker and test flags ############################################
CC_FLAGS =	-Wall -Wextra -Werror
LD_FLAGS =	-rcs
LT_FLAGS =	--tag CXX --mode=link cc
T_FLAGS = 	-lcriterion

# debugging or optimilization flags #########################################
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

# os variables ##############################################################
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

# daily submodule autoupdate ################################################
GIT_MODULES=.refresh
TIME := $(shell date +'%d')
ifneq ("$(wildcard $(GIT_MODULES))","")
    LAST_UPDATE=$(shell cat $(GIT_MODULES))
    ifneq ($(LAST_UPDATE),$(TIME))
        $(shell rm -f $(GIT_MODULES))
    endif
endif

# make commands #############################################################
all: $(NAME)

$(GIT_MODULES):
	@$(ECHO) "Updating submodules..."
	@git submodule update --init --remote
	@$(ECHO) $(shell date +'%d') > $(GIT_MODULES)
	@$(ECHO) "$(OK_STRING)\n"

submodule:
	@git submodule update --init --remote --recursive

# this is incredibly hacky, but there seems to be no other portable way to
# combine static libs using standard makefiles...
# https://stackoverflow.com/questions/24954747/how-to-use-libtool-to-create
# -a-static-library-from-a-bunch-of-static-libraries
$(NAME): $(ALLDEPS)
	@$(ECHO) "Linking $(NAME)..."
	@mkdir -p artmp
	@list='$^'; for p in $$list; do											\
	    (cd artmp; ar x "../$$p"; ar q "../$@" *.o; rm *.o) || false 2>$(CC_LOG); done
	@rm -rf artmp
	@ranlib $@ 2> $(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(COMMON): $(GIT_MODULES) $(LIBGNL) $(LIBFT) $(LOGGER) $(OBJ_D) $(OBJ)
	@$(ECHO) "Linking $(COMMON)..."
	@$(LD) $(LD_FLAGS) $(COMMON) $(OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(TREE): $(GIT_MODULES) $(LIBFT) $(LOGGER) $(OBJ_D) $(TREE_OBJ)
	@$(ECHO) "Linking $(TREE)..."
	@$(LD) $(LD_FLAGS) $(TREE) $(TREE_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LOGGER): $(GIT_MODULES) $(LIBFT) $(OBJ_D) $(LOG_OBJ)
	@$(ECHO) "Linking $(LOGGER)..."
	@$(LD) $(LD_FLAGS) $(LOGGER) $(LOG_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(GRAMMARGENERATOR): $(GIT_MODULES) $(LIBGNL) $(LIBFT) $(LIBVECTOR) $(LOGGER)\
		$(OBJ_D) $(GG_OBJ)
	@$(ECHO) "Linking $(GRAMMARGENERATOR)..."
	@$(LD) $(LD_FLAGS) $(GRAMMARGENERATOR) $(GG_OBJ) 2>$(CC_LOG)			\
	|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LEXER): $(GIT_MODULES) $(LIBFT) $(LIBVECTOR) $(LOGGER)					\
		$(OBJ_D) $(LEX_OBJ)
	@$(ECHO) "Linking $(LEXER)..."
	@$(LD) $(LD_FLAGS) $(LEXER) $(LEX_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(PARSER): $(GIT_MODULES) $(LIBFT) $(LIBVECTOR) $(LOGGER)					\
		$(OBJ_D) $(PARSE_OBJ)
	@$(ECHO) "Linking $(PARSER)..."
	@$(LD) $(LD_FLAGS) $(PARSER) $(PARSE_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG) && false; elif test -s $(CC_LOG); then $(ECHO)		\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(OBJ_D):
	@mkdir -p $(OBJ_D)
	@mkdir -p $(OBJ_D)/common
	@mkdir -p $(OBJ_D)/tree
	@mkdir -p $(OBJ_D)/logger
	@mkdir -p $(OBJ_D)/grammargenerator
	@mkdir -p $(OBJ_D)/lexer
	@mkdir -p $(OBJ_D)/parser

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(TREE_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LOG_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(GG_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LEX_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(PARSE_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG)		\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LIBGNL):
	@$(MAKE) -C $(LIB_D)/libgnl

$(LIBFT):
	@$(MAKE) -C $(LIB_D)/libft

$(LIBVECTOR):
	@$(MAKE) -C $(LIB_D)/libvector

clean:
	@$(RM) $(OBJ)
	@$(RM) -r *.dSYM
	@$(RM) *.testbin
	@$(RM) -r artmp
	@$(RM) -r $(OBJ_D)
	@$(MAKE) -C $(LIB_D)/libgnl clean || true
	@$(MAKE) -C $(LIB_D)/libft clean || true
	@$(MAKE) -C $(LIB_D)/libvector clean || true

fclean: clean
	@$(RM) $(ALLDEPS) $(NAME)
	@$(MAKE) -C $(LIB_D)/libgnl fclean || true
	@$(MAKE) -C $(LIB_D)/libft fclean || true
	@$(MAKE) -C $(LIB_D)/libvector fclean || true

norm:
	@norminette $(SRC) $(INC)

re: fclean all

basics_test: TEST='basics_t'
basics_test: $(NAME) $(ALLDEPS)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC)-o $(TEST).testbin	\
		tests/$(TEST).c $(NAME) $(ALLDEPS) $(LIBGNL) $(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin examples/bash.bnf "$(CMD)"
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

grammargenerator_test: TEST='grammargenerator_t'
grammargenerator_test: $(GRAMMARGENERATOR)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC) -o $(TEST).testbin	\
		tests/$(TEST).c $(ALLDEPS) $(LIBGNL) $(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin examples/bash.bnf
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

lexer_test: TEST='lexer_t'
lexer_test: $(GRAMMARGENERATOR) $(LEXER)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC) -o $(TEST).testbin	\
		tests/$(TEST).c $(ALLDEPS) $(LOGGER) $(LIBGNL) $(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin examples/bash.bnf "$(CMD)"
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

tests:
	@$(MAKE) ASAN=1 re
	@$(MAKE) ASAN=1 basics_test
	@$(MAKE) ASAN=1 grammargenerator_test
	@$(MAKE) ASAN=1 lexer_test

.PHONY: all clean fclean re tests
