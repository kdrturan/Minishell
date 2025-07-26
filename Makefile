NAME        = minishell

PATH_SRC    = src
PATH_OBJ    = obj

SUBDIRS     = signal token utils init env _GC debug lexer parser parser/complete_pipe parser/cmd_utils parser/redir_utils parser/check_syntax exec exec/built_in

PATH_LIBFT  = lib/libft
LIBFT       = $(PATH_LIBFT)/libft.a

SRC_DIRS    = $(PATH_SRC) $(addprefix $(PATH_SRC)/,$(SUBDIRS))
OBJ_SUBDIRS = $(addprefix $(PATH_OBJ)/,$(SUBDIRS))

BASE_INC_DIRS = include $(PATH_LIBFT)
INC_DIRS      = $(addprefix $(PATH_SRC)/,$(SUBDIRS))
PATH_INCLUDE  = $(addprefix -I ,$(BASE_INC_DIRS) $(INC_DIRS))

CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/_GC/gc.c \
	src/debug/debug_cmd.c \
	src/debug/debug_env.c \
	src/debug/debug_token.c \
	src/env/env_add.c \
	src/env/env_cast_char.c \
	src/env/env_get_value.c \
	src/env/env_len.c \
	src/env/env_parse.c \
	src/env/env_remove.c \
	src/env/env_set.c \
	src/exec/built_in/built_in.c \
	src/exec/built_in/cd.c \
	src/exec/built_in/echo.c \
	src/exec/built_in/env.c \
	src/exec/built_in/exit.c \
	src/exec/built_in/export.c \
	src/exec/built_in/pwd.c \
	src/exec/built_in/unset.c \
	src/exec/exec.c \
	src/exec/exec_pipeline.c \
	src/exec/exec_preprocess.c \
	src/exec/exec_redir.c \
	src/exec/exec_run.c \
	src/exec/heredoc.c \
	src/exec/process_utils.c \
	src/init/init.c \
	src/lexer/identify_tokens.c \
	src/lexer/lexer.c \
	src/main.c \
	src/parser/check_syntax/check_syntax.c \
	src/parser/check_syntax/check_utils.c \
	src/parser/cmd_utils/cmd_add_back.c \
	src/parser/cmd_utils/cmd_clean.c \
	src/parser/cmd_utils/cmd_last.c \
	src/parser/cmd_utils/cmd_new.c \
	src/parser/generate_commands.c \
	src/parser/handle_dollar.c \
	src/parser/merge_words.c \
	src/parser/parse_preprocess.c \
	src/parser/parse_quote_utils.c \
	src/parser/parser.c \
	src/parser/redir_utils/redir_add_back.c \
	src/parser/redir_utils/redir_last.c \
	src/parser/redir_utils/redir_new.c \
	src/signal/signal_handler.c \
	src/token/token_add_back.c \
	src/token/token_clean.c \
	src/token/token_insert.c \
	src/token/token_last.c \
	src/token/token_new.c \
	src/token/token_remove.c \
	src/utils/c_exit.c \
	src/utils/exit_code.c \
	src/utils/ft_getpid.c \
	src/utils/get_prompt.c \
	src/utils/is_interrupted.c \
	src/utils/print_error.c \
	src/utils/utils_env.c \
	src/utils/utils_str.c \
	src/utils/utils_token.c

OBJS = $(patsubst $(PATH_SRC)/%, \
                  $(PATH_OBJ)/%, \
                  $(SRCS:.c=.o))

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_PATH := $(shell brew --prefix readline 2>/dev/null)
	CHECK_PREFIX  := $(shell brew --prefix check 2>/dev/null)
	PATH_INCLUDE  += -I$(READLINE_PATH)/include -I$(CHECK_PREFIX)/include
	LIBS = -L$(READLINE_PATH)/lib -L$(CHECK_PREFIX)/lib -lreadline -lhistory -lncurses $(LIBFT)
else ifeq ($(UNAME_S),Linux)
	CHECK_PREFIX  := /usr
	PATH_INCLUDE  += -I/usr/include -I/usr/include/readline -I$(CHECK_PREFIX)/include
	LIBS = -L$(CHECK_PREFIX)/lib -lreadline -lhistory -lncurses $(LIBFT)
endif

all: $(NAME)

$(LIBFT):
	@make -C $(PATH_LIBFT) all

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ) $(OBJ_SUBDIRS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c | $(PATH_OBJ)
	@$(CC) $(CFLAGS) $(PATH_INCLUDE) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@make -s -C $(PATH_LIBFT) clean
	@$(RM) -r $(PATH_OBJ) build.log

fclean: clean
	@make -s -C $(PATH_LIBFT) fclean
	@$(RM) -r $(NAME)

re: fclean all

update_libs:
	rm -rf lib
	git clone https://github.com/Tuncayarda/Libft.git lib/libft

setup_env:
	git remote set-url --add --push origin git@github.com:Tuncayarda/Minishell.git
	git remote set-url --add --push origin git@github.com:kdrturan/Minishell.git

run_valgrind:
	@valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --suppressions=valgrind.supp \
	         --quiet \
	         ./minishell

.PHONY: all clean fclean re update_libs setup_env run_valgrind help 
