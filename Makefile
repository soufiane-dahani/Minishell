SRCS = minishell.c error.c 
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = #-Wall -Wextra -Werror
LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

LDFLAGS = -L$(LIBFT_DIR) -lft

$(LIBFT_LIB):
	cd $(LIBFT_DIR) && make

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)


all: $(NAME)

clean:
	$(RM) $(OBJS)
	cd $(LIBFT_DIR) && make clean


fclean: clean
	$(RM) $(NAME)
	cd $(LIBFT_DIR) && make fclean


re: fclean all


.PHONY: all clean fclean re
.SECONDARY:
