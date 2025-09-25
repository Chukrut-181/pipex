**pipex - Unix Pipeline Recreation | 42 Academy | Score: 125/100 | Completed: October 10th, 2024**

📋 **Project Overview**  

pipex is an advanced 42 Academy project that recreates the behavior of Unix shell pipelines, recreating the shell command **< file1 cmd1 | cmd2 >file2** by creating child processes and establishing communication channels between them.
Challenge: Implement Unix pipeline functionality from scratch managing multiple processes and file descriptors.

🔧 **Key Technical Skills Developed**

- Process Management: Creating and managing child processes using fork() and execve()
- Inter-Process Communication: Implementing pipes for data flow between processes
- File Descriptor Manipulation: Advanced dup2() usage for input/output redirection
- Command Parsing: Parsing and preparing commands with arguments for execution
- Path Resolution: Finding executable commands in system PATH environment
- System Calls Mastery: Working with low-level Unix system calls (fork, pipe, execve, wait)
- Error Handling: Comprehensive error management for system call failures

🚀 **Learning Outcomes**

- Unix System Programming: Deep understanding of Unix process model and IPC mechanisms
- Shell Internals: Insight into how shell pipelines work at the operating system level
- Concurrent Programming: Managing multiple simultaneous processes and their interactions
- System Architecture: Understanding the relationship between processes, files, and system resources

🌱 **Personal Growth**

- Systems Thinking: Developed understanding of complex multi-process architectures
- Debugging Complexity: Enhanced skills in debugging multi-process applications
- Resource Awareness: Learned critical importance of proper resource cleanup in system programming

🛠️ **Technical Specifications**

- Language: C
- Compilation: Makefile with -Wall -Wextra -Werror flags
- Code Standard: 42 Norminette compliance
- System Calls: Extensive use of Unix system calls for process and file management
- Bonus Features: Multiple pipeline support and here_doc functionality (125/100 score achievement)

🎓 **Academic Recognition**

- Final Score: 125/100 (Bonus completed - multiple pipes and here_doc)
- Evaluation: Rigorous peer evaluation
- Technical Impact: Foundation for understanding shell programming and system administration tools
