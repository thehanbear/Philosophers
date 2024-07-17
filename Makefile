NAME = philo

SRCS = src/routine.c src/main.c src/utils.c \
		src/init.c src/check.c src/print.c

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	@cc $(CFLAGS) $^ -o $@ 
	@echo " \n$(Yellow)"

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
	@echo "\n$(Ending)"


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
	@echo "\n$(Ending)"

re: fclean all

.PHONY: all clean fclean re


Green = \033[0;32m
Yellow = \033[0;33m
Ending = \033[0m
