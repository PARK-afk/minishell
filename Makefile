NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Werror -Wextra
SRC     = $(wildcard ./srcs/builtin/*.c) $(wildcard ./srcs/execute/*.c) $(wildcard ./srcs/parse/*.c) $(wildcard ./srcs/*.c)
LIBFT   = -L ./libft -lft
OBJ     = $(SRC:.c=.o)
HEADER  = ./mini.h

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@make -C ./libft
	@$(CC) $(CFLAGS) -I $(HEADER) $(LIBFT) -L ~/readline -lreadline -lncurses -lhistory $(OBJ) -o $(NAME)

.c.o :
	@$(CC) $(CFLAGS) -I $(HEADER) -c -o $@ $<

clean :
	@rm -rf $(OBJ)
	@make clean -C ./libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re
