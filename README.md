# philosophers-42
100/100

# Introduction
A number of philosophers are sitting at a round table doing one of three things:
eating, thinking or sleeping. While eating, they are not thinking or sleeping, while sleeping, they are not eating
or thinking and of course, while thinking, they are not eating or sleeping. The philosophers sit at a circular table with a large bowl of spaghetti in the center. There are some forks on the table to serve and eat, one for each hand. Every philosopher needs to eat. Each time a philosopher has finished eating, he will drop his forks and start sleeping. When a philosopher is done sleeping, he will start thinking. The simulation stops when a philosopher dies.

# Mandatory part
philo_one:
- One fork between each philosopher, therefore there will be a fork at the right and
at the left of each philosopher.

- To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.

- Each philosopher should be a thread.

- External functions allowed: memset, malloc, free, write, usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock

philo_two:
- All the forks are in the middle of the table.

- They have no states in memory but the number of available forks is represented by
a semaphore.

- Each philosopher should be a thread.

- External functions allowed: memset, malloc, free, write, usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
sem_open, sem_close, sem_post, sem_wait, sem_unlink

philo_three:
- All the forks are in the middle of the table.

- They have no states in memory but the number of available forks is represented by
a semaphore.

- Each philosopher should be a process and the main process should not be a philosopher

- External functions allowed: memset, malloc, free, write, fork, kill, exit,
pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink