#SETUP
NAME		=	pipex
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS	=	pipex.c pipex_utils.c pipex_errors.c
MPATH_DIR	=	mandatory/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

BPATH_SRCS	=	pipex_bonus.c pipex_utils_bonus.c pipex_errors_bonus.c
BPATH_DIR	=	bonus/
BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(BPATH:.c=.o)

FPATH_SRCS	=	ft_calloc.c ft_split.c ft_strdup.c ft_strjoin.c\
				ft_strlcpy.c ft_strlen.c ft_strncmp.c
FPATH_DIR	=	functions/
FPATH		=	$(addprefix $(FPATH_DIR), $(FPATH_SRCS))
OBJ_F		=	$(FPATH:.c=.o)

#COMMANDS
%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_M) $(OBJ_F)
				@$(CC) $(OBJ_M) $(OBJ_F) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

bonus:			$(OBJ_B) $(OBJ_F)
				@$(CC) $(OBJ_B) $(OBJ_F) -o $(NAME)
				@echo "$(GREEN)$(NAME) bonus created!$(DEFAULT)"

clean:
				@$(RM) $(OBJ_M) $(OBJ_B) $(OBJ_F)
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