###############################################################################
###############################################################################

NAME = minishell

###############################################################################
###############################################################################

CC			 =		cc
CFLAGS		=		-Wall -Werror -Wextra -g
EXTRA_FLAGS		=	-lreadline
HEADERS		=		-I./includes -I./libs/inlcude

###############################################################################
###############################################################################

VPATH		:=		src src/lexer src/builtins src/exec src/expander src/init

SRC_MAIN	:=		main.c
SRC_LEXER	:=		move_to_next_token.c # quots_check.c lexer.c
SRC_BUIN	:=		builtins_cd.c builtins.c builtins_utils.c
SRC_EXEC	:=		exec_utils.c executor.c heredoc_handling.c redirect.c
SRC_EXPAND	:=		expander.c
SRC_INIT	:=		init_env.c
SRC_UTILS	:=		ft_split.c

SOURCE 		:=		$(SRC_MAIN) $(SRC_LEXER) $(SRC_BUIN) $(SRC_EXEC) \
					$(SRC_EXPAND) $(SRC_INIT) $(SRC_UTILS)

###############################################################################
###############################################################################

OBJ_DIR		:=		./_obj
OBJ			:=		$(addprefix $(OBJ_DIR)/, $(SOURCE:%.c=%.o))

###############################################################################
###############################################################################

all : $(NAME)

$(NAME): $(OBJ) $(LIBS_NAME)
	@echo $(YELLOW)Compiling [$(NAME)]...$(RESET)
	@printf $(UP)$(CUT)
	@git submodule update --init --recursive -q
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(EXTRA_FLAGS)
	@echo $(GREEN)Finished"  "[$(NAME)]...$(RESET)

$(OBJ_DIR)/%.o: %.c
	@echo $(YELLOW)Compiling [$@]...$(RESET)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@
	@printf $(UP)$(CUT)

$(LIBS_NAME):
	@$(MAKE) -C $(LIBS) -B

###############################################################################
###############################################################################

clean:
	@$(MAKE) -C ./libs clean
	@if [ -d "${OBJ_DIR}" ]; then \
			echo $(RED)Cleaning"  "[$(OBJ_DIR)]...$(RESET); \
			rm -rf ${OBJ_DIR}; \
			echo $(GREEN)Cleaned!$(RESET); \
	fi

###############################################################################
###############################################################################

fclean: clean
		@make -C ./libs fclean
		@if [ -f "$(NAME)" ]; then \
				echo $(RED)Cleaning"  "[$(NAME)]...$(RESET);	\
				rm -f $(NAME); \
				echo $(GREEN)Cleaned!$(RESET); \
		fi

re: fclean all

#@printf $(UP)$(CUT)
#@printf $(UP)$(CUT)
###############################################################################
###############################################################################

.PHONY : clean fclean all re

###############################################################################
###############################################################################

YELLOW := "\033[33m"
RED := "\033[31m"
GREEN := "\033[32m"
RESET := "\033[0m"
UP := "\033[A"
CUT := "\033[K"
