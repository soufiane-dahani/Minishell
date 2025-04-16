# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 12:11:50 by yaait-am          #+#    #+#              #
#    Updated: 2025/04/14 15:20:52 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
TARGET = minishell
SRC = main.c handle_signal.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c \
	libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c libft_used/ft_lstnew.c malloc.c libft_used/ft_strncmp.c \
	parsing.c is.c t_ast.c is_the_cmd_valid.c first_worderr.c to_linked.c check_the.c pars_cmd.c creat_new_node.c \
	build_tree.c
OBJ = $(SRC:.c=.o)

all: $(TARGET) # banner

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean # bye
	@rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re

banner :
	@echo "\033[34m  _______  _________ _       _________ _______           _______  _        _       \033[0m"
	@echo "\033[34m (       )\__   __/( (    /|\__   __/(  ____ \|\     /|(  ____ \( \      ( \      \033[0m"
	@echo "\033[34m | () () |   ) (   |  \  ( |   ) (   | (    \/| )   ( || (    \/| (      | (      \033[0m"
	@echo "\033[34m | || || |   | |   |   \ | |   | |   | (_____ | (___) || (__    | |      | |      \033[0m"
	@echo "\033[34m | |(_)| |   | |   | (\ \) |   | |   (_____  )|  ___  ||  __)   | |      | |      \033[0m"
	@echo "\033[34m | |   | |   | |   | | \   |   | |         ) || (   ) || (      | |      | |      \033[0m"
	@echo "\033[34m | )   ( |___) (___| )  \  |___) (___/\____) || )   ( || (____/\| (____/\| (____/\033[0m"
	@echo "\033[34m |/     \|\_______/|/    )_)\_______/\_______)|/     \|(_______/(_______/(_______/\033[0m"
	@echo "\033[32m                       🚀 Welcome to MiniShell! 🚀                          \033[0m"

bye :
	@echo "\033[31m  _______             _        _______  _    ______   _______  _        _ _________   _        _______  _______           _______  \033[0m"
	@echo "\033[31m (  ___  )|\     /|  ( (    /|(  ___  )( )  (  __  \ (  ___  )( (    /|( )\__   __/  ( \      (  ____ \(  ___  )|\     /|(  ____ \ \033[0m"
	@echo "\033[31m | (   ) || )   ( |  |  \  ( || (   ) || |  | (  \  )| (   ) ||  \  ( ||/    ) (     | (      | (    \/| (   ) || )   ( || (    \/ \033[0m"
	@echo "\033[31m | |   | || (___) |  |   \ | || |   | || |  | |   ) || |   | ||   \ | |      | |     | |      | (__    | (___) || |   | || (__     \033[0m"
	@echo "\033[31m | |   | ||  ___  |  | (\ \) || |   | || |  | |   | || |   | || (\ \) |      | |     | |      |  __)   |  ___  |( (   ) )|  __)    \033[0m"
	@echo "\033[31m | |   | || (   ) |  | | \   || |   | |(_)  | |   ) || |   | || | \   |      | |     | |      | (      | (   ) | \ \_/ / | (       \033[0m"
	@echo "\033[31m | (___) || )   ( |  | )  \  || (___) | _   | (__/  )| (___) || )  \  |      | |     | (____/\| (____/\| )   ( |  \   /  | (____/\ \033[0m"
	@echo "\033[31m (_______)|/     \|  |/    )_)(_______)(_)  (______/ (_______)|/    )_)      )_(     (_______/(_______/|/     \|   \_/   (_______/ \033[0m"
	@echo "\033[32m                                                           See you next time!                          \033[0m"
