#SETUP
NAME		=	pipex
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS	=	pipex.c pipex_utils.c str_utils.c ft_split.c ft_calloc.c
MPATH_DIR	=	mandatory/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

BPATH_SRCS	=	pipex_bonus.c pipex_utils_bonus.c str_utils_bonus.c\
				ft_split_bonus.c ft_calloc_bonus.c
BPATH_DIR	=	bonus/
BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(BPATH:.c=.o)

#COMMANDS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_M)
				@$(CC) $(OBJ_M) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)


bonus:			$(OBJ_B)
				@$(CC) $(OBJ_B) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_B)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all bonus clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m