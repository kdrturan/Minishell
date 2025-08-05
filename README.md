Minishell – A Simple Linux Shell Simulator
Minishell is a Linux command-line shell simulator written in C. It reads user input, breaks it down into tokens (lexical analysis), parses the syntax into structured commands, and executes them using fork/exec system calls. It supports both built-in commands and external programs with features like piping, redirection, and environment variable expansion.

🔧 Features
Lexical analysis and command parsing: Splits user input into tokens and parses them into a command table.

Built-in and external commands: Supports commands like cd, echo, pwd, exit, as well as external programs like ls, cat, etc.

Environment variable expansion: Recognizes and expands variables like $HOME, $PATH.

Pipes and I/O redirection: Supports Unix-style pipes (|) and redirection operators (>, <).

Signal handling: Responds to user signals (e.g., Ctrl+C) and handles them gracefully without crashing.

🧱 Project Structure
Tokenizer: Reads the input line character by character and splits it into tokens using spaces and special characters as delimiters.

Parser: Analyzes the token list and builds a command table representing the execution plan.

Executor: Forks a new process for each command and runs it using execve. Also handles pipes, redirection, and built-in commands.

⚙️ Installation & Usage
Clone the repository:

bash
Copy
Edit
git clone https://github.com/kdrturan/Minishell.git
Navigate to the project folder:

bash
Copy
Edit
cd Minishell
Compile the source code:
If a Makefile is included:

bash
Copy
Edit
make
Or manually with GCC:

bash
Copy
Edit
gcc *.c -o minishell
Run the shell:

bash
Copy
Edit
./minishell
⚠️ Note: This project is designed to run on Unix-like systems (Linux/macOS). Windows is not supported due to POSIX dependencies.

💡 Example Usage
bash
Copy
Edit
$ ./minishell
minishell> echo "Hello World"
Hello World
minishell> ls -l
(total 16)
-rw-r--r-- 1 user user  123 Jan  1 12:34 README.md
-rw-r--r-- 1 user user 1024 Jan  1 12:34 main.c
minishell> cd ..
minishell> pwd
/home/user
minishell> cat file.txt | grep "example" > result.txt
minishell> exit
📋 Requirements
Compiler: GCC 5.2.0 or higher with C99/C11 support.

Make (optional): For easy build with Makefile.

OS: Linux or Unix-like environment (POSIX compliant).

🤝 Contributing
This is an open-source project. Contributions, bug reports, or feature suggestions are welcome! Feel free to fork the repository and open a pull request. Contribution guidelines may be available in a CONTRIBUTING.md file if present.

📄 License
This project is under the copyright of the author. Please refer to the LICENSE file (if available) for licensing details. If not specified, it is assumed to be under default copyright.
