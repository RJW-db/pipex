# Pipex

Pipex is a small UNIX mechanism project written in C. Its goal is to reproduce the behavior of shell pipes and redirections while learning how processes, file descriptors, pipes, and command execution work together.

This repository follows the Pipex subject closely: it implements the mandatory two-command pipeline, PATH-based execution, file redirections, clean process handling, and the bonus features for multiple pipes and heredoc.

## Features

- Reproduces the behavior of:  
  `< file1 cmd1 | cmd2 > file2`
- Command execution with `execve`
- PATH-based command lookup
- Input and output redirections
- Pipe creation and file-descriptor duplication
- Proper child-process creation and waiting
- Shell-like error handling
- Clean memory and file-descriptor management

### Bonus

- Multiple pipes:  
  `./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`
- Heredoc support:  
  `./pipex here_doc LIMITER cmd1 cmd2 file`

## Table of Contents

- [Project Scope](#project-scope)
- [Instructions](#instructions)
- [Build](#build)
- [Usage](#usage)
- [Architecture and Implementation](#architecture-and-implementation)
  - [Program flow](#program-flow)
  - [Command parsing](#command-parsing)
  - [PATH resolution](#path-resolution)
  - [Pipes and file descriptors](#pipes-and-file-descriptors)
  - [Process creation and execution](#process-creation-and-execution)
  - [Error handling and cleanup](#error-handling-and-cleanup)
  - [Bonus logic](#bonus-logic)
- [Resources](#resources)
- [License](#license)

## Project Scope

<details>
<summary><strong>Subject rules and scope</strong></summary>

### Core rules

Pipex must reproduce the essential behavior of a small shell pipeline:

- Show the equivalent behavior of:
  ```bash
  ./pipex file1 cmd1 cmd2 file2
  ```
- Match:
  ```bash
  < file1 cmd1 | cmd2 > file2
  ```
- `file1` and `file2` are file names.
- `cmd1` and `cmd2` are shell commands with their parameters.
- The program must open the input file, create a pipe, execute both commands, and write the result to the output file.
- The program must handle errors without crashing.
- All allocated memory must be freed properly.


The Makefile must provide at least:

- `all`
- `$(NAME)`
- `clean`
- `fclean`
- `re`

and should avoid unnecessary relinking.

### Allowed functions

The Pipex subject allows the following external functions:

- `open`, `close`, `read`, `write`
- `malloc`, `free`
- `perror`, `strerror`
- `access`
- `dup`, `dup2`
- `execve`
- `exit`
- `fork`
- `pipe`
- `unlink`
- `wait`, `waitpid`
- `ft_printf` or an equivalent function you coded yourself

### Notes

- The project must be written in C.
- It must follow the 42 Norm.
- Your program must not crash unexpectedly.
- All allocated memory must be freed.
- Memory leaks are not tolerated.
- The Makefile must compile with `cc` and the flags `-Wall -Wextra -Werror`.

### Mandatory part

The mandatory part is the two-command pipeline:

- one input file
- two commands
- one pipe between the commands
- one output file

This is the core behavior required by the subject and should behave like the shell command above.

### Bonus part

Bonus features may include:

- Multiple pipes:
  ```bash
  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
  ```
  which behaves like:
  ```bash
  < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
  ```

- Heredoc support when the first argument is `here_doc`:
  ```bash
  ./pipex here_doc LIMITER cmd cmd1 file
  ```
  which behaves like:
  ```bash
  cmd << LIMITER | cmd1 >> file
  ```

The bonus part is evaluated only if the mandatory part is perfect.

</details>

## Instructions

### Prerequisites

Before building Pipex, make sure the following are available:

- A C compiler compatible with the project `Makefile`
- The allowed system calls and functions required by the subject
- Your `libft` library, if your project uses it

## Build

Build the project with:

```bash
make
make clean
make fclean
make re
```

## Usage

### Mandatory

Run the program as:

```bash
./pipex file1 "cmd1" "cmd2" file2
```

Examples:

```bash
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
```

Equivalent shell behavior:

```bash
< infile ls -l | wc -l > outfile
< infile grep a1 | wc -w > outfile
```

### Bonus

Multiple pipes:

```bash
./pipex file1 "cmd1" "cmd2" "cmd3" ... "cmdn" file2
```

Equivalent shell behavior:

```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

Heredoc:

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" file
```

Equivalent shell behavior:

```bash
cmd << LIMITER | cmd2 >> file
```

The bonus part is only evaluated if the mandatory part is fully correct and functional.

## Architecture and Implementation

### Program flow

The execution starts in the [entry point](src/main.c) and moves through the [pipeline executor](src/pipex.c), where the shell-like flow opens files, creates pipes, forks children, redirects file descriptors, and waits for completion. At a high level, the first command reads from the input file, writes into the pipe, and the second command reads from the pipe and writes into the output file.

### Command parsing

The [child process handler](src/pipex_child_processes.c) prepares each command before execution by splitting the command string into its executable name and arguments. This creates the `argv` array that is later passed to `execve`.

### PATH resolution

When a command is not an absolute path, the [child process handler](src/pipex_child_processes.c) resolves it through the `PATH` environment variable. It searches each directory, joins it with the command name, and checks access until it finds an executable match.

### Pipes and file descriptors

The core of the project is file-descriptor routing, managed by the [pipeline executor](src/pipex.c) and the [forking helpers](src/pipex_forking_utils.c). For the mandatory part, `file1` becomes stdin for `cmd1`, the write end of the pipe becomes stdout for `cmd1`, the read end of the pipe becomes stdin for `cmd2`, and `file2` becomes stdout for `cmd2`. This is handled with `dup2`, followed by careful closing of unused file descriptors in both the parent and child processes.

### Process creation and execution

Each command runs in a child process created with `fork`, then calls `execve` after redirections are in place. The parent closes the unnecessary ends of the pipe, waits for children with `wait` or `waitpid`, and keeps the shell stable even if one command fails.

### Error handling and cleanup

The [forking helpers](src/pipex_forking_utils.c) and [writing helper](src/writing.c) centralize error handling so the program fails cleanly instead of crashing. Common failure cases include files that cannot be opened, commands that do not exist, commands that are not executable, and system call failures such as `pipe`, `fork`, or `dup2`. The implementation protects shell state by checking every system-call return value, closing file descriptors on failure paths, freeing allocated memory, and printing useful error messages.

### Bonus logic

The [heredoc bonus](src/pipex_heredoc_bonus.c) extends the mandatory pipeline into a multi-command flow when multiple pipes are enabled. It also handles `here_doc` by reading from standard input until the limiter is reached, then opening the output file in append mode so the behavior matches the subject specification.

## Resources

Classic references for Pipex:

- [The Open Group Base Specifications, Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Linux manual: pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [Linux manual: fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Linux manual: dup(2)](https://man7.org/linux/man-pages/man2/dup.2.html)
- [Linux manual: execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)
- [Linux manual: wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html)
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)

## License

This project is licensed under the [MIT License](LICENSE).