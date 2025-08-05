# 🐚 Minishell – A Simple Linux Shell Simulator

**Minishell** is a Linux command-line shell simulator written in C. It reads user input, breaks it down into tokens (lexical analysis), parses the syntax into structured commands, and executes them using `fork`/`exec` system calls. It supports built-in commands, external programs, environment variable expansion, piping, and redirection.

---

## 🔧 Features

- **Lexical analysis and parsing**: Input is tokenized and transformed into executable command structures.
- **Built-in & external command support**: Includes `cd`, `echo`, `pwd`, `exit`, and supports external binaries like `ls`, `cat`, etc.
- **Environment variable expansion**: Interprets variables like `$HOME`, `$PATH`.
- **Pipes & redirection**: Supports `|`, `>`, `<`, and combined operators.
- **Signal handling**: Handles Ctrl+C and similar signals gracefully.

---

## 🧱 Architecture

- **Tokenizer**: Scans the input string and splits it into meaningful tokens.
- **Parser**: Validates token sequences and builds command tables.
- **Executor**: Executes each command with support for piping, redirection, and built-ins.

---

## ⚙️ Installation & Usage

```bash
# 1. Clone the repository
git clone https://github.com/kdrturan/Minishell.git

# 2. Navigate into the project directory
cd Minishell

# 3. Build the project
make          # if a Makefile is provided

# Or manually compile:
gcc *.c -o minishell

# 4. Run the shell
./minishell

Note: POSIX-compliant OS required (Linux/macOS). Windows is not supported.

💡 Example Session

$ ./minishell
minishell> echo "Hello World"
Hello World
minishell> ls -l
total 16
-rw-r--r-- 1 user user  123 Jan  1 12:34 README.md
-rw-r--r-- 1 user user 1024 Jan  1 12:34 main.c
minishell> cd ..
minishell> pwd
/home/user
minishell> cat file.txt | grep "example" > result.txt
minishell> exit


Requirements
GCC ≥ 5.2.0

Make (optional)

Linux or Unix-like OS with POSIX support
