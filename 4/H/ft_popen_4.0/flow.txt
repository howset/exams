START ft_popen(file, argv, type)
|
├── Check if type is valid ('r' or 'w')
|   └── If invalid, return -1
|
├── Create a pipe with pipe(fd)
|   └── If pipe creation fails, return -1
|
├── Fork a process with pid = fork()
|   |
|   ├── If fork fails (pid == -1)
|   |   ├── Close both pipe ends (fd[0] and fd[1])
|   |   └── Return -1
|   |
|   ├── If in child process (pid == 0)
|   |   |
|   |   ├── If type == 'r' (reading from child)
|   |   |   ├── Close read end of pipe (fd[0])
|   |   |   ├── Redirect stdout to write end (dup2(fd[1], STDOUT_FILENO))
|   |   |   |   └── If dup2 fails, exit with failure
|   |   |   └── Close duplicated fd (fd[1])
|   |   |
|   |   ├── If type == 'w' (writing to child)
|   |   |   ├── Close write end of pipe (fd[1])
|   |   |   ├── Redirect stdin to read end (dup2(fd[0], STDIN_FILENO))
|   |   |   |   └── If dup2 fails, exit with failure
|   |   |   └── Close duplicated fd (fd[0])
|   |   |
|   |   ├── Execute the command (execvp(file, argv))
|   |   └── If execvp returns (failure), exit with failure
|   |
|   └── If in parent process
|       |
|       ├── If type == 'r' (parent reads from child)
|       |   ├── Close write end of pipe (fd[1])
|       |   └── Set fd_to_return = fd[0] (read end)
|       |
|       ├── If type == 'w' (parent writes to child)
|       |   ├── Close read end of pipe (fd[0])
|       |   └── Set fd_to_return = fd[1] (write end)
|       |
|       └── Return fd_to_return
|
END