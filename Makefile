NAME = minishell

CFLAGS = -g -fsanitize=address  #-Wall -Wextra -Werror

PATH_LIBFT = lib/libft

PATH_SRC = src
PATH_PARSER = $(PATH_SRC)/parser
PATH_SIGNAL = $(PATH_SRC)/signal
PATH_TOKEN = $(PATH_SRC)/token
PATH_UTILS = $(PATH_SRC)/utils
PATH_ENV = $(PATH_SRC)/env
PATH_INIT = $(PATH_SRC)/init
PATH_DEBUG = $(PATH_SRC)/debug

PATH_OBJ = obj

LIBFT = $(PATH_LIBFT)/libft.a

PATH_INCLUDE =	-I include \
				-I $(PATH_LIBFT) -I $(PATH_PARSER) \
				-I $(PATH_TOKEN) -I $(PATH_SIGNAL) \
				-I $(PATH_UTILS) -I $(PATH_DEBUG) \
				-I $(PATH_ENV)   -I $(PATH_INIT)

SRCS =	$(wildcard $(PATH_SRC)/*.c) \
		$(wildcard $(PATH_PARSER)/*.c) \
		$(wildcard $(PATH_TOKEN)/*.c) \
		$(wildcard $(PATH_SIGNAL)/*.c) \
		$(wildcard $(PATH_UTILS)/*.c) \
		$(wildcard $(PATH_INIT)/*.c) \
		$(wildcard $(PATH_ENV)/*.c) \
		$(wildcard $(PATH_DEBUG)/*.c) 

OBJS = $(SRCS:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_PATH := $(shell brew --prefix readline 2>/dev/null)
	PATH_INCLUDE += -I $(READLINE_PATH)/include
	LIBS = -L$(READLINE_PATH)/lib -lreadline -lhistory -lncurses $(LIBFT)
else
	LIBS = -lreadline -lhistory -lncurses $(LIBFT)
endif

all: $(NAME)

$(LIBFT):
	make -C $(PATH_LIBFT) all

$(PATH_OBJ):
	@mkdir obj
	@mkdir obj/parser
	@mkdir obj/signal
	@mkdir obj/token
	@mkdir obj/utils
	@mkdir obj/init
	@mkdir obj/env
	@mkdir obj/debug

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

update_libs:
	rm -rf lib
	git clone https://github.com/Tuncayarda/Libft.git lib/libft

setup_env:
	git remote set-url --add --push origin git@github.com:Tuncayarda/Minishell.git
	git remote set-url --add --push origin git@github.com:kdrturan/Minishell.git

.PHONY: all clean fclean re