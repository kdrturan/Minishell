NAME = minishell

CFLAGS = -Wall -Wextra -Werror

PATH_INCLUDE = include

PATH_SRC = src
PATH_PARSER = $(PATH_SRC)/parser

PATH_OBJ = obj

MAIN_SRCS = *.c
PARSE_SRCS = *.c

SRCS =	$(addprefix $(PATH_SRC)/, $(MAIN_SRCS)) \
		$(addprefix $(PATH_PARSER)/, $(PARSE_SRCS)) 

OBJS = $(SRCS:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

LIBS = -lreadline

all: $(NAME)

$(PATH_OBJ):
	@mkdir obj
	@mkdir obj/parser

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c | $(PATH_OBJ)
	$(CC) $(CFLAGS) -I $(PATH_INCLUDE) -o $@ -c $?

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@$(RM) -r $(PATH_OBJ)

fclean: clean
	@$(RM) -r $(NAME)

re: fclean all

.PHONY: all clean fclean re