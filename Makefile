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

CFLAGS =   -g

vpath %.c $(SRC_DIRS)

SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

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

STOP_ANIM = \
	kill -TERM $$anim_pid 2>/dev/null || true; \
	pkill -TERM -P $$anim_pid 2>/dev/null || true

all:
	@{ \
		( exec bash -c 'trap "exit" INT TERM; \
		  while true; do $(MAKE) -s -C ascii_anim ascii_anim; done' \
		) 2>/dev/null & \
		anim_pid=$$!; \
		$(MAKE) --no-print-directory $(NAME) >build.log 2>&1; status=$$?; \
		$(STOP_ANIM); \
		wait $$anim_pid 2>/dev/null || true; \
		if [ $$status -eq 0 ]; then \
			printf '\033c'; echo "✅  Build succeeded"; rm -f build.log; \
		else \
			printf '\033c'; echo "❌  Build failed. Last 100 lines of log:"; \
			tail -n 100 build.log; \
		fi; \
		exit $$status; \
	}

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

TEST_NAME = test_parser
TEST_SRC  = $(wildcard tests/test_parser/*.c) tests/test.c
TEST_OBJS = $(filter-out $(PATH_OBJ)/main.o, $(OBJS))

test_parse: $(LIBFT) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_OBJS) -o $(TEST_NAME) \
		$(PATH_INCLUDE) $(LIBS)
	@./$(TEST_NAME)
	@rm -f $(TEST_NAME)

help:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║                    Available Make Targets                  ║"
	@echo "╠════════════════════════════════════════════════════════════╣"
	@echo "║ make              │ Build the project with ASCII animation ║"
	@echo "║ make all          │ Same as 'make' (includes animation)    ║"
	@echo "║ make minishell    │ Compile only the minishell binary      ║"
	@echo "║ make clean        │ Remove object files and build log      ║"
	@echo "║ make fclean       │ Clean everything including binary      ║"
	@echo "║ make re           │ Rebuild the project from scratch       ║"
	@echo "║ make update_libs  │ Clone/update libft from GitHub         ║"
	@echo "║ make setup_env    │ Set Git remotes for pushing branches   ║"
	@echo "║ make run_valgrind │ Run Valgrind with memory checks        ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""

.PHONY: all clean fclean re update_libs setup_env run_valgrind help 