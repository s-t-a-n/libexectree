# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/25 18:13:09 by sverschu      #+#    #+#                  #
#    Updated: 2020/09/20 19:48:40 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= libexectree.a

# internal libraries ########################################################
COMMON          = common.a
LOGGER			= logger.a
LEXERGENERATOR	= lexergenerator.a
LEXER			= lexer.a
ALLDEPS         = $(COMMON) $(LOGGER) $(LEXERGENERATOR) $(LEXER)

# directories ###############################################################
SRC_D = src
OBJ_D = obj
INC_D = inc
LIB_D = lib

# common source files ######################################################
SRC =	$(SRC_D)/common/common.c											\

OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### logger source files
LOG_SRC=$(SRC_D)/logger/logger.c											\

LOG_OBJ :=	$(LOG_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### lexer generator source files
LG_SRC =$(SRC_D)/lexergenerator/lexer_ir.c									\
		$(SRC_D)/lexergenerator/lexer_ir_lifetime.c							\
		$(SRC_D)/lexergenerator/lg_process_nonterminal.c					\
		$(SRC_D)/lexergenerator/lg_process_definitions.c					\
		$(SRC_D)/lexergenerator/lg_definition_lifetime.c					\
		$(SRC_D)/lexergenerator/lg_node_lifetime.c							\
		$(SRC_D)/lexergenerator/lg_token_lifetime.c							\
		$(SRC_D)/lexergenerator/lg_dump.c									\
		$(SRC_D)/lexergenerator/lg_search.c									\
		$(SRC_D)/lexergenerator/lg_post_processing.c						\

LG_OBJ :=	$(LG_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

### lexer source files
LEX_SRC =$(SRC_D)/lexer/lexer.c												\

LEX_OBJ :=	$(LEX_SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

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
LT_FLAGS =	--mode=link gcc -g -O
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

$(NAME): $(GIT_MODULES) $(LIBGNL) $(LIBFT) $(LIBVECTOR) $(LOGGER)			\
		$(LEXERGENERATOR) $(LEXER) $(COMMON)
	@$(ECHO) "Linking $(NAME)..."
	@$(LT) $(LT_FLAGS) -o $(NAME) $(ALLDEPS) 1>/dev/null 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(COMMON): $(GIT_MODULES) $(LIBGNL) $(LIBFT) $(LOGGER) $(OBJ_D) $(OBJ)
	@$(ECHO) "Linking $(COMMON)..."
	@$(LD) $(LD_FLAGS) $(COMMON) $(OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LOGGER): $(GIT_MODULES) $(LIBFT) $(OBJ_D) $(LOG_OBJ)
	@$(ECHO) "Linking $(LOGGER)..."
	@$(LD) $(LD_FLAGS) $(LOGGER) $(LOG_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LEXERGENERATOR): $(GIT_MODULES) $(LIBGNL) $(LIBFT) $(LIBVECTOR) $(LOGGER)	\
		$(OBJ_D) $(LG_OBJ)
	@$(ECHO) "Linking $(LEXERGENERATOR)..."
	@$(LD) $(LD_FLAGS) $(LEXERGENERATOR) $(LG_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LEXER): $(GIT_MODULES) $(LIBFT) $(LIBVECTOR) $(LOGGER)	\
		$(OBJ_D) $(LEX_OBJ)
	@$(ECHO) "Linking $(LEXER)..."
	@$(LD) $(LD_FLAGS) $(LEXER) $(LEX_OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(OBJ_D):
	@mkdir -p $(OBJ_D)
	@mkdir -p $(OBJ_D)/common
	@mkdir -p $(OBJ_D)/logger
	@mkdir -p $(OBJ_D)/lexergenerator
	@mkdir -p $(OBJ_D)/lexer

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
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

$(LG_OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
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

$(LIBGNL):
	@make -C $(LIB_D)/libgnl

$(LIBFT):
	@make -C $(LIB_D)/libft

$(LIBVECTOR):
	@make -C $(LIB_D)/libvector

clean:
	@$(RM) $(OBJ)
	@$(RM) -r *.dSYM
	@$(RM) *.testbin
	@$(RM) -r $(OBJ_D)
	@make -C $(LIB_D)/libgnl clean || true
	@make -C $(LIB_D)/libft clean || true
	@make -C $(LIB_D)/libvector clean || true

fclean: clean
	@$(RM) $(ALLDEPS) $(NAME)
	@make -C $(LIB_D)/libgnl fclean || true
	@make -C $(LIB_D)/libft fclean || true
	@make -C $(LIB_D)/libvector fclean || true

norm:
	@norminette $(SRC) $(INC)

re: fclean all

basics_crit_test: TEST='basics_crit_t'
basics_crit_test: $(NAME)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC) -o $(TEST).testbin	\
		tests/$(TEST).c $(NAME)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"				\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)				\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin $(CRIT_FLAGS) && $(RM) -f $(TEST).testbin		\
		&& $(RM) -rf $(TEST).dSYM 2>$(CC_LOG)
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

basics_test: TEST='basics_t'
basics_test: $(NAME)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC)-o $(TEST).testbin	\
		tests/$(TEST).c $(NAME) $(LIBGNL) $(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"	\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)	\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin $(CRIT_FLAGS) && $(RM) -f $(TEST).testbin		\
		&& $(RM) -rf $(TEST).dSYM 2>$(CC_LOG)
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

lexer_generator_test: TEST='lexer_generator_t'
lexer_generator_test: $(LEXERGENERATOR)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC) -o $(TEST).testbin	\
		tests/$(TEST).c $(LEXERGENERATOR) $(LOGGER) $(LIBGNL) $(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"	\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)	\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin examples/bash.bnf $(CRIT_FLAGS)				\
		&& $(RM) -f $(TEST).testbin && $(RM) -rf $(TEST).dSYM 2>$(CC_LOG)
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

lexer_test: TEST='lexer_t'
lexer_test: $(LEXERGENERATOR) $(LEXER)
	@$(ECHO) "Compiling $(TEST).c..." 2>$(CC_LOG) || touch $(CC_ERROR)
	@$(CC) $(CC_FLAGS) $(T_FLAGS) -I$(INC_D) $(LIB_INC) -o $(TEST).testbin	\
		tests/$(TEST).c $(LEXERGENERATOR) $(LEXER) $(LOGGER) $(LIBGNL)		\
		$(LIBFT) $(LIBVECTOR)
	@if test -e $(CC_ERROR); then $(ECHO) "$(ERROR_STRING)\n"	\
	 && $(CAT) $(CC_LOG); elif test -s $(CC_LOG); then $(ECHO)	\
	 "$(WARN_STRING)\n" && $(CAT) $(CC_LOG); else $(ECHO) "$(OK_STRING)\n"; fi
	@$(ECHO) "Running $(TEST)...\n"
	@$(DBG) ./$(TEST).testbin examples/bash.bnf $(CRIT_FLAGS)				\
		&& $(RM) -f $(TEST).testbin && $(RM) -rf $(TEST).dSYM 2>$(CC_LOG)
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

tests: $(NAME)
	@make ASAN=1 re
	@make ASAN=1 basics_test
	@make ASAN=1 lexer_generator_test
	@make ASAN=1 lexer_test

.PHONY = all clean fclean re
