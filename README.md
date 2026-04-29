# 🐚 cmpsh - Custom Minimalist Powerful Shell

`cmpsh` is a custom-built, lightweight Unix-like shell implemented in C. It serves as a command-line interface that bridges the gap between the user and the operating system, supporting both interactive terminal sessions and non-interactive script execution.

---

## 🚀 Features

### 🛠️ Built-in Commands
`cmpsh` includes several core commands implemented directly within the shell for efficiency and control:
- **`exit`**: Terminate the shell session gracefully.
- **`cd [directory]`**: Change the current working directory.
- **`pwd`**: Print the absolute path of the current working directory.
- **`path [dir1] [dir2] ...`**: Configure the search paths for external executables. Calling `path` without arguments clears all search paths.

### 🔄 Advanced Functionality
- **Piping (`|`)**: Chain multiple commands together, passing the output of one as the input to the next.
- **Redirection (`>`)**: Reroute the standard output of a command to a specified file.
- **External Execution**: Seamlessly run any external program found in the shell's path list using `fork()` and `execv()`.
- **Script Support**: Run a series of commands from a file by passing the filename as an argument.

### 🛡️ Robust Design
- **Non-interactive Mode**: Execute batch scripts with ease.
- **Input Parsing**: Handles quoted strings and whitespace efficiently.
- **Process Management**: Correctly waits for child processes and handles I/O redirection.

---

## 🏗️ Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`)
- `make` build utility
- A Unix-like environment (Linux, macOS, WSL)

### Compilation
Navigate to the source directory and use the provided `Makefile`:

```bash
cd src/requirement
make
```

This will generate the `cmpsh` executable.

### Usage

#### Interactive Mode
Simply run the executable to start the shell:
```bash
./cmpsh
```
You will see the prompt: `cmpsh>`.

#### Script Mode
To execute a script file:
```bash
./cmpsh scripts/my_script.sh
```

---

## 📂 Project Structure

- **`src/requirement/`**: The core source code of the shell.
  - `cmpsh.c`: Entry point and main shell loop.
  - `executes.h`: Command execution logic and built-ins.
  - `readingIns.h`: Input parsing and tokenization.
  - `ss.h`: Alternative execution implementations.
  - `Makefile`: Build instructions.
- **`src/examples/`**: A collection of C programs for testing signals and error handling.
- **`src/requirement/test_scripts/`**: Sample shell scripts to validate shell behavior.

---

## 🧪 Testing
The `src/examples` directory contains several programs (e.g., `signal01.c` to `signal07.c`) that can be compiled and run within `cmpsh` to test signal propagation and process management.

---


