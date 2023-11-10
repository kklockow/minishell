###############################################################################
###############################################################################

NAME = minishell

###############################################################################
###############################################################################

CC			 =		cc
CFLAGS		=		-Wall -Werror -Wextra
EXTRA_FLAGS		=	-lreadline
HEADERS		=		-I./includes -I./libs/inlcude

###############################################################################
###############################################################################

VPATH		:=		src

SRC_MAIN	:=		main.c

SOURCE 		:=		$(SRC_MAIN)

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
	@printf $(UP)$(CUT)
	@if [ -d "${OBJ_DIR}" ]; then \
			echo $(RED)Cleaning"  "[$(OBJ_DIR)]...$(RESET); \
			rm -rf ${OBJ_DIR}; \
			echo $(GREEN)Cleaned!$(RESET); \
	fi

###############################################################################
###############################################################################

fclean: clean
		@echo $(RED)Cleaning executables...
		@make -C ./libs fclean
		@printf $(UP)$(CUT)
		@if [ -f "$(NAME)" ]; then \
				echo $(RED)Cleaning"  "[$(NAME)]...$(RESET); \
				rm -f $(NAME); \
				echo $(GREEN)Cleaned!$(RESET); \
		fi

re: fclean all

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
