# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 12:11:50 by yaait-am          #+#    #+#              #
#    Updated: 2025/05/12 12:34:54 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -L -lft

TARGET = minishell
SRC = minishell.c parsing/main.c parsing/handle_signal.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c \
	libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c libft_used/ft_lstnew.c parsing/malloc.c libft_used/ft_strncmp.c \
	parsing/parsing.c parsing/is_function.c parsing/start_building_ast.c parsing/is_the_cmd_valid.c parsing/first_word_error.c \
	parsing/creat_the_linked.c parsing/helper_func_to_build_ast.c parsing/helper_function.c parsing/creat_new_node.c parsing/build_the_ast.c \
	parsing/nb_of_token.c parsing/handel_quote.c parsing/get_the_env.c parsing/handle_red_herdoc.c parsing/helper_function_for_tree.c \
	parsing/exp_for_herdoc.c\
	exc/exc.c exc/error.c exc/builtins_cd.c exc/helper_fun.c exc/help_exp_before_func.c\
	exc/builtins_pwd.c exc/builtins_exit.c exc/builtins_env.c exc/builtins_unset.c exc/builtins_export.c \
	exc/helper_fun2.c exc/exec_external.c exc/exec_pipe.c exc/exec_redirection.c  \
	exc/exec_and.c exc/exec_subshell.c exc/builtins_cd_help.c exc/builtins_echo.c exc/builtins_export_help.c \
	exc/builtins_export_help2.c exc/builtins_export_help3.c libft_exc/ft_isdigit.c \
	libft_exc/ft_itoa.c libft_exc/ft_isalpha.c libft_exc/ft_memcpy.c libft_exc/ft_putchar_fd.c \
	libft_exc/ft_putstr_fd.c libft_exc/ft_split.c libft_exc/ft_strchr.c libft_exc/ft_strlcat.c libft_exc/ft_strnstr.c\
	libft_exc/ft_strlcpy.c exc/help_exp_before_func2.c parsing/help.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re banner bye
