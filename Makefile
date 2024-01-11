###############################################################################
###############################################################################

NAME = minishell

###############################################################################
###############################################################################

CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra #-fsanitize=address -g
EXTRA_FLAGS		=		-lreadline
HEADERS			=		-I./includes -I./libs/include
LIBS			=		./libs
LIBS_NAME		=		./libs/libs.a

###############################################################################
###############################################################################

VPATH		:=		src src/lexer src/command_table src/utils src/init		\
					src/builtins src/exec src/expander src/signals			\
					src/free_structs src/setup_structs

SRC_MAIN	:=		main.c
SRC_LEXER	:=		lexer.c find_quote_pair.c add_token_node.c				\
					go_to_last_lexer_node.c double_greater_and_smaler.c		\
					get_single_tokens.c tag_word.c skip_whitespace.c		\
					time_to_lex.c
SRC_CMD_TAB	:=		command_table.c syntax_error_print.c syntax_check.c		\
					redirect_rules_check.c pipe_roules_check.c				\
					is_redirect.c fill_command_struct.c						\
					command_node_add_back.c add_space_check.c				\
					heredoc_argument.c repeat_set_data_next_save.c
SRC_UTILS	:=		get_input.c stop_process.c								\
					input_check.c set_error_code.c stop_loop.c				\
					if_null_stop_process.c get_structs.c
SRC_INIT	:=		init.c init_env.c
SRC_BUIN	:=		builtins_cd.c builtins.c builtins_utils_00.c			\
					builtins_exit.c builtins_export.c builtins_utils_01.c
SRC_EXEC	:=		exec_utils00.c executor.c heredoc_handling.c redirect.c \
					exec_utils01.c
SRC_EXPAND	:=		expander.c update_cmd.c expand_to_home.c expander_utils.c
SRC_SIGNAL	:=		catch_signals.c command_c.c command_quit.c				\
					hide_ctrl_chars.c handle_signal_in_child.c
SRC_FREE	:=		free_lexer_struct.c parser_free.c						\
					save_free.c shell_struct_free.c free_command_struct.c
SRC_SETUP	:=		setup_structs.c first_setup.c

SOURCE 		:=		$(SRC_MAIN) $(SRC_LEXER) $(SRC_CMD_TAB) $(SRC_UTILS)	\
					$(SRC_INIT) $(SRC_BUIN) $(SRC_EXEC) $(SRC_EXPAND)		\
					$(SRC_SIGNAL) $(SRC_FREE) $(SRC_SETUP)

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
	@if [ ! -d "${OBJ_DIR}" ]; then							\
		mkdir -p _obj;										\
	fi
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
