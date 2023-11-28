###############################################################################
###############################################################################

NAME = minishell

###############################################################################
###############################################################################

CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra -g
EXTRA_FLAGS		=		-lreadline
HEADERS			=		-I./includes -I./libs/include
LIBS			=		./libs
LIBS_NAME		=		./libs/libs.a

###############################################################################
###############################################################################

VPATH		:=		src src/lexer

SRC_MAIN	:=		main.c
SRC_LEXER	:=		lexer.c find_quote_pair.c add_token_node.c				\
					go_to_last_lexer_node.c set_up_lexer_struct.c			\
					double_greater_and_smaler.c get_single_tokens.c			\
					tag_word.c skip_whitespace.c

SOURCE 		:=		$(SRC_MAIN) $(SRC_LEXER)

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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS_NAME) -o $(NAME) $(EXTRA_FLAGS)
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
