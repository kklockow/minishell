###############################################################################
###############################################################################

NAME = minishell

###############################################################################
###############################################################################

CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra -fsanitize=address -g
EXTRA_FLAGS		=		-lreadline
HEADERS			=		-I./includes -I./libs/include
LIBS			=		./libs
LIBS_NAME		=		./libs/libs.a

###############################################################################
###############################################################################

VPATH		:=		src src/lexer src/command_table src/utils src/init		\
					src/builtins src/exec src/expander src/init

SRC_MAIN	:=		main.c
SRC_LEXER	:=		lexer.c find_quote_pair.c add_token_node.c				\
					go_to_last_lexer_node.c double_greater_and_smaler.c		\
					get_single_tokens.c tag_word.c skip_whitespace.c		\
					time_to_lex.c free_struct_and_stop_lexing.c
SRC_CMD_TAB	:=		command_table.c syntax_error_print.c syntax_check.c		\
					redirect_rules_check.c pipe_roules_check.c				\
					is_redirect.c fill_command_struct.c						\
					command_node_add_back.c
SRC_UTILS	:=		setup_structs.c get_input.c set_process.c
SRC_INIT	:=		init.c
SRC_BUIN	:=		builtins_cd.c builtins.c builtins_utils.c
SRC_EXEC	:=		exec_utils.c executor.c heredoc_handling.c redirect.c
SRC_EXPAND	:=		expander.c
SRC_INIT	:=		init_env.c
SRC_UTILS	:=		ft_split.c

SOURCE 		:=		$(SRC_MAIN) $(SRC_LEXER) $(SRC_CMD_TAB) $(SRC_UTILS)	\
					$(SRC_INIT) $(SRC_BUIN) $(SRC_EXEC) $(SRC_EXPAND)		\
					$(SRC_INIT) $(SRC_UTILS)
>>>>>>> parser

###############################################################################
###############################################################################

OBJ_DIR		:=		./_obj
OBJ			:=		$(addprefix $(OBJ_DIR)/, $(SOURCE:%.c=%.o))

###############################################################################
###############################################################################

all : $(NAME)

$(NAME): $(LIBS_NAME) $(OBJ)
	@echo $(YELLOW)Compiling [$(NAME)]...$(RESET)
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS_NAME) -o $(NAME) $(EXTRA_FLAGS)
	@echo $(GREEN)Finished"  "[$(NAME)]...$(RESET)

$(OBJ_DIR)/%.o: %.c
	@echo $(YELLOW)Compiling [$@]...$(RESET)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@
	@printf $(UP)$(CUT)

$(LIBS_NAME):
	@git submodule update --remote --init -q
	@$(MAKE) -C $(LIBS) -B

###############################################################################
###############################################################################

clean:
	@if [ -d "${OBJ_DIR}" ]; then							\
			$(MAKE) -C ./libs clean;						\
			echo $(RED)Cleaning"  "[$(OBJ_DIR)]...$(RESET);	\
			rm -rf ${OBJ_DIR};								\
			echo $(GREEN)Cleaned!$(RESET);					\
	fi

###############################################################################
###############################################################################

fclean: clean
		@if [ -f "$(NAME)" ]; then								\
				$(MAKE) -C ./libs fclean;						\
				echo $(RED)Cleaning"  "[$(NAME)]...$(RESET);	\
				rm -f $(NAME);									\
				echo $(GREEN)Cleaned!$(RESET);					\
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
