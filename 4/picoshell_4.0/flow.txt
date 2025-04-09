START picoshell(cmds)
|
├── Initialize variables:
|   ├── i = 0 (command index)
|   └── prev_fd = 0 (previous pipe read end, initially stdin)
|
├── LOOP while cmds[i] exists
|   |
|   ├── If there's a next command (cmds[i+1])
|   |   └── Create a new pipe with pipe(fd)
|   |
|   ├── Fork a process with pid = fork()
|   |   |
|   |   ├── If in child process (pid == 0)
|   |   |   |
|   |   |   ├── If prev_fd != 0 (not first command)
|   |   |   |   ├── Redirect stdin to previous pipe read end (dup2(prev_fd, STDIN_FILENO))
|   |   |   |   └── Close prev_fd
|   |   |   |
|   |   |   ├── If there's a next command (cmds[i+1])
|   |   |   |   ├── Close read end of new pipe (fd[0])
|   |   |   |   ├── Redirect stdout to write end (dup2(fd[1], STDOUT_FILENO))
|   |   |   |   └── Close write end of new pipe (fd[1])
|   |   |   |
|   |   |   ├── Execute the command (execvp(cmds[i][0], cmds[i]))
|   |   |   └── If execvp returns (failure), exit with code 1
|   |   |
|   |   └── If in parent process
|   |       |
|   |       ├── If prev_fd != 0 (not first command)
|   |       |   └── Close prev_fd (no longer needed)
|   |       |
|   |       └── If there's a next command (cmds[i+1])
|   |           ├── Close write end of new pipe (fd[1])
|   |           └── Set prev_fd = fd[0] (read end for next command)
|   |
|   └── Increment i for next command
|
├── LOOP while wait(&status) > 0 (wait for all child processes)
|   └── If any child exited abnormally or with non-zero status
|       └── Return 1 (error)
|
└── Return 0 (success)