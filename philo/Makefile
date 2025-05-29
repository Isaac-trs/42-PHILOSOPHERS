GREEN = \033[0;92m
YELLOW = \033[0;93m
RED = \033[0;91m
CYAN = \033[0;96m
RESET= \033[0m

NAME = philosophers

SRCS = main.c functions.c debug.c philos.c routine.c monitor.c

CC = cc

HEADER = philosophers.h
CFLAGS = -Wall -Werror -Wextra -lpthread -g3 -fsanitize=thread 

all:	$(NAME)

$(NAME): $(OBJS)
		@echo "$(YELLOW)Compiling $(CYAN)obj files $(YELLOW)..."
		@${CC} $(SRCS) $(CFLAGS) -o $(NAME)
		@echo "$(CYAN)$(NAME) $(GREEN)has been successfully created !$(RESET)"



clean:
	@echo "$(YELLOW)Removing $(NAME) $(CYAN)object files$(YELLOW) ...$(RESET)"
	@rm -rf objs
	@echo "$(GREEN)philosophers $(CYAN)object files $(GREEN)cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME) $(CYAN)program$(YELLOW) ...$(RESET)"
	@rm $(NAME)
	@echo "$(GREEN)$(NAME) successfully $(RED)deleted$(GREEN) !$(RESET)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt $(CYAN)everything for $(NAME)$(RESET)"

.PHONY: all clean fclean re 