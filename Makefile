NAME = pipex

NAME_BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = pipex.c pipex_utils.c ft_split.c general_utils.c general_utils2.c error.c

SOURCES_BONUS = pipex_bonus.c pipex_utils_bonus.c ft_split.c general_utils_bonus.c general_utils2_bonus.c error_bonus.c create_tmp_bonus.c

INCLUDE = pipex.h

INCLUDE_BONUS = pipex_bonus.h

OBJS = $(SOURCES:.c=.o)

OBJS_BONUS = $(SOURCES_BONUS:.c=.o)

GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}Pipex compilation OK${RESET}"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "${GREEN}Pipex_bonus compilation OK${RESET}"

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	@echo "${YELLOW}All objects removed${RESET}"

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	@echo "${RED}Pipex removed${RESET}"
	@echo "${RED}Pipex_bonus removed${RESET}"

re: fclean all

.PHONY: all clean fclean re