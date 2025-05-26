NAME = minishell

CFLAGS = #-fsanitize=address -g #-Wall -Wextra -Werror

PATH_LIBFT = lib/libft

PATH_SRC = src
PATH_PARSER = $(PATH_SRC)/parser
PATH_TOKEN = $(PATH_SRC)/token

PATH_OBJ = obj

LIBFT = $(PATH_LIBFT)/libft.a

PATH_INCLUDE = -I include -I $(PATH_LIBFT) -I $(PATH_TOKEN)

MAIN_SRCS = main.c
PARSE_SRCS = parse.c
TOKEN_SRCS = token_add_back.c token_clear.c token_del.c token_new.c token_remove.c

SRCS =	$(addprefix $(PATH_SRC)/, $(MAIN_SRCS)) \
		$(addprefix $(PATH_PARSER)/, $(PARSE_SRCS)) \
		$(addprefix $(PATH_TOKEN)/, $(TOKEN_SRCS))

OBJS = $(SRCS:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

LIBS = -lreadline $(LIBFT)

all: $(NAME)

$(LIBFT):
	make -C $(PATH_LIBFT) all

$(PATH_OBJ):
	@mkdir obj
	@mkdir obj/parser
	@mkdir obj/token

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c | $(PATH_OBJ)
	$(CC) $(CFLAGS) $(PATH_INCLUDE) -o $@ -c $?

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@make -C $(PATH_LIBFT) clean
	@$(RM) -r $(PATH_OBJ)

fclean: clean
	@make -C $(PATH_LIBFT) fclean
	@$(RM) -r $(NAME)

re: fclean all

.PHONY: all clean fclean re