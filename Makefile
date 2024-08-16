# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 14:09:11 by hlee-sun          #+#    #+#              #
#    Updated: 2024/07/17 15:33:21 by hlee-sun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/routine.c src/main.c src/utils.c \
		src/init.c src/check.c src/print.c src/forks.c

CFLAGS = -Wall -Wextra -Werror -pthread

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $@ 
	@echo "\n$(Green)"

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@'~~~     ~~~\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@'                     \`@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@'                           \`@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@'                               \`@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@'              P H I L O            \`@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@'                                     \`@@@@@@@@@@@@"
	@echo "@@@@@@@@@'                                       \`@@@@@@@@@@@"
	@echo "@@@@@@@@@                                         @@@@@@@@@@@"
	@echo "@@@@@@@@'                      n,                 \`@@@@@@@@@@"
	@echo "@@@@@@@@                     _/ | _                @@@@@@@@@@"
	@echo "@@@@@@@@                    /'  \`'/                @@@@@@@@@@"
	@echo "@@@@@@@@a                 <~    .'                a@@@@@@@@@@"
	@echo "@@@@@@@@@                 .'    |                 @@@@@@@@@@@"
	@echo "@@@@@@@@@a              _/      |                a@@@@@@@@@@@"
	@echo "@@@@@@@@@@a           _/      \`.\`.              a@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@a     ____/ '   \__ | |______       a@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@a__/___/      /__\ \ \     \___.a@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@/  (___.'\_______)\_|_|        \@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@|\________                       ~~~~~\@@@@@@@@@@"
	@echo " "

clean:
	@rm -rf $(OBJS)
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f $(NAME)
	@echo " \n$(Green)"
	@echo "               _____"
	@echo "              /     \\"
	@echo "              vvvvvvv  /|__/|"
	@echo "                 I   /O.O   |"
	@echo "                 I /_____   |      /|/|"
	@echo "                 J/^ ^ ^ \\  |    /00  |    _//|"
	@echo "                 |^ ^ ^ ^ |W|   |/^^\\ |   /oo |"
	@echo "   All clean      \\m___m__|_|    \\m_m_|   \\mm_|"
	@echo " "

re: fclean all

.PHONY: all clean fclean re

Green = '\033[32m'
Ending = '\033[0m'
