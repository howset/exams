```
START sandbox(f, timeout, verbose)
|
├── Fork a process with pid = fork()
|   |
|   ├── If fork fails (pid == -1)
|   |   └── Return -1 (error)
|   |
|   ├── If in child process (pid == 0)
|   |   ├── Execute function f()
|   |   └── If f() returns, exit with SUCCESS
|   |
|   └── If in parent process
|       |
|       ├── Set up signal handler for SIGALRM
|       |   └── Handler sets g_flag = 0 when alarm triggers
|       |
|       ├── Set alarm(timeout)
|       |
|       ├── Wait for child process (waitpid(pid, &status, 0))
|       |   |
|       |   ├── If waitpid fails (== -1)
|       |   |   |
|       |   |   └── Enter error handling loop
|       |   |       |
|       |   |       ├── If error is EINTR (interrupted by signal)
|       |   |       |   |
|       |   |       |   ├── If g_flag is set
|       |   |       |   |   ├── If verbose, print timeout value
|       |   |       |   |   ├── Kill child process (kill(pid, SIGKILL))
|       |   |       |   |   ├── Clean up zombie (waitpid(pid, &status, 0))
|       |   |       |   |   |   └── If cleanup fails, return -1
|       |   |       |   |   └── Return 0 (bad function)
|       |   |       |   |
|       |   |       |   └── If not g_flag, continue loop
|       |   |       |
|       |   |       └── For other errors, return -1
|       |   |
|       |   └── If waitpid succeeds
|       |       |
|       |       ├── If child exited normally (WIFEXITED)
|       |       |   |
|       |       |   ├── Get exit code (WEXITSTATUS)
|       |       |   |
|       |       |   ├── If exit code == 0
|       |       |   |   ├── If verbose, print "Nice!"
|       |       |   |   └── Return 1 (nice function)
|       |       |   |
|       |       |   └── If exit code != 0
|       |       |       ├── If verbose, print exit code
|       |       |       └── Return 0 (bad function)
|       |       |
|       |       ├── If child terminated by signal (WIFSIGNALED - misspelled as WIFESIGNALED)
|       |       |   ├── Print signal description (missing verbose check)
|       |       |   └── Return 0 (bad function)
|       |       |
|       |       └── For any other case, return -1
|
END
```