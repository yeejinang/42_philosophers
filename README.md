# 42_philosophers

## Overview
Dining philosophers often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
Synchronization is a cooperating process which can affect or be affected by other processes executing in the system.
Problem may faced in synchronization:
1. Starvation:
    One or more threads in your program are blocked from gaining access to a resource and, as a result, cannot make progress.
2. Deadlock:
    Ultimate form of starvation, occurs when two or more threads are waiting on a condition that cannot be satisfied. 
    Deadlock most often occurs when two (or more) threads are each waiting for the other(s) to do something.
    Solution: First fork always be the lowest number fork. 
    <br />Philo 1: Pick up Fork 1 first.
    <br />Philo 2: Pick up Fork 2 first.
    <br />Philo 3: Pick up Fork 3 first.
    <br />Philo 4: Pick up Fork 4 first.
    <br />Philo 5: Pick up Fork 1 first.
    <br />Fork 5 is not locked by philo, thus Philo 1 can access into Fork 5 and start eating.
3. Data Race:
    When 2 or more threads (philosophers) trying to access a shared resources (fork)
    Solution:
    Mandatory: Mutex
    Bonus: Semaphore

## Threads and Processes
| Thread                                           | Process                                          |
|--------------------------------------------------|--------------------------------------------------|
| Segment of a process                             | Any program is in execution                      |
| Shared memory with its peer threads              | Independent and do not share memory              |
| Shared data segment, code segment, files etc     | Independent data and code segments               |
| Less time for creation and termination           | More time for creation and termination           |
### Functions for thread:
pthread_create:
<br />pthread_detach:
<br />pthread_join:
### Functions for process:
fork:
<br />kill:
<br />waitpid: 
[Fork().pdf](https://github.com/yeejinang/42_philosophers/files/8212411/Fork.pdf)

## Mutex
Locking mechanism used to synchronize access to a resource. Only one philo allowed to access critical section at one time.
In this project, we will need mutex for 3 parts
1. Mutex for each forks
2. Mutex when printing out statement (displayed state message should not mixed up with another message)
3. Mutex between checking the death of philo and when the philo is eating.
    (As we will save the philo last meal and checking philo's death by comparing time of last meal and current time, current_time - last_meal < time_to_die)
### Functions
pthread_mutex_init:
<br />pthread_mutex_destroy:
<br />pthread_mutex_lock:
<br />pthread_mutex_unlock:

## Semaphore
Signaling mechinism.
### Functions

### Resources:
1. Short Intro to Threads (Playlist by CodeVault)
    https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2 
2. Difference between processes and threads
    https://www.youtube.com/watch?v=IKG1P4rgm54
3. 
