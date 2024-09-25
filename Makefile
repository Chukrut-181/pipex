NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = pipex.c pipex_utils.c ft_split.c general_utils.c general_utils2.c error.c

OBJS = $(SOURCES:.c=.o)

GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}Pipex compilation OK${RESET}"

clean:
	rm -f $(OBJS)
	@echo "${YELLOW}All objects removed${RESET}"

fclean: clean
	rm -f $(NAME)
	@echo "${RED}Pipex removed${RESET}"

re: fclean all

.PHONY: all clean fclean re