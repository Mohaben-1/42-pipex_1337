# pipex - 1337 Project  

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/) 
![Status](https://img.shields.io/badge/Status-Completed-brightgreen) ![Grade](https://img.shields.io/badge/Grade-125%2F100-success)

## 📜 Project Overview  

**pipex** is a Unix pipeline simulation project from **1337** (part of the **42 Network**). The project replicates shell pipe functionality (`cmd1 | cmd2`) with file redirections, implementing both mandatory and bonus features including multiple pipes and here_doc functionality.

---

## 🚀 Features  

### Mandatory Part  
- Simulates shell pipes: `< file1 cmd1 | cmd2 > file2`  
- Handles file input/output redirection  
- Robust error handling for files and commands  

### Bonus Part  
- Supports multiple pipes: `cmd1 | cmd2 | cmd3 | ... | cmdn`  
- Implements here_doc (`<< delimiter`) functionality  
- Handles file appending (`>>`)  
- Includes custom utility functions (GNL, string operations)  

---

## 📂 Repository Structure  

```plaintext
📦 pipex
├── Bonus part
│   ├── pipex_bonus.c
│   ├── ft_split_bonus.c
│   ├── ft_strjoin_bonus.c
│   ├── handle_fds_bonus.c
│   ├── cmd_handle_bonus.c
│   ├── get_next_line_bonus.c
│   ├── utils_bonus.c
│   ├── pipex_bonus.h
│
├── Mandatory part
│   ├── pipex.c     
│   ├── ft_split.c
│   ├── ft_strjoin.c
│   ├── utils.c
│   ├── handle_fds.c
|   ├── cmd_handle.c
│   ├── pipex.h
│
└── 📜 Makefile
```

---

## 🛠️ Compilation  

### Mandatory  
```bash
make
```
Produces `pipex` executable  

### Bonus  
```bash
make bonus
```
Produces `pipex` executable  

### Cleanup  
```bash
make clean      # Remove object files
make fclean     # Remove executables and objects
make re         # Full recompile
```

---

## 📖 Usage Examples  

### Basic Pipe  
```bash
./pipex infile "cat" "cat" outfile
```
Equivalent to:  
```bash
< infile cat | cat > outfile
```

### Multiple Pipes (Bonus)  
```bash
./pipex infile "grep foo" "sort" "uniq" outfile
```

### here_doc (Bonus)  
```bash
./pipex here_doc EOF "cat" "wc -w" outfile
```
Then type input ending with EOF

---

## 🛡️ Error Handling  
- Invalid file permissions  
- Non-existent commands  
- Memory leak protection  
- Argument validation  

---

## 🌟 Key Functions  
- `fork()`/`execve()` process management  
- `pipe()`/`dup2()` file descriptor handling  
- Custom string utilities (GNL, splitting, joining)  
- Comprehensive error checking  

---

## 📋 Norm Compliance  
- Follows 42 School coding standards  
- No memory leaks  
- Clean Makefile structure

For complete requirements, see [en.subject.pdf](subject/en.subject.pdf).
