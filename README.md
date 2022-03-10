# 42_philosophers

## Overview :mag:
Dining philosophers often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
Synchronization is a cooperating process which can affect or be affected by other processes executing in the system.
Problem may faced in synchronization:
<br />**1. Starvation**
    <br />One or more threads in your program are blocked from gaining access to a resource and, as a result, cannot make progress.
<br />**2. Deadlock**
    <br />Ultimate form of starvation, occurs when two or more threads are waiting on a condition that cannot be satisfied. 
    Deadlock most often occurs when two (or more) threads are each waiting for the other(s) to do something.
    <br />Solution: First fork always be the lowest number fork. 
    <br />Philo 1: Pick up Fork 1 first.
    <br />Philo 2: Pick up Fork 2 first.
    <br />Philo 3: Pick up Fork 3 first.
    <br />Philo 4: Pick up Fork 4 first.
    <br />Philo 5: Pick up Fork 1 first.
    <br />Fork 5 is not locked by philo, thus Philo 1 can access into Fork 5 and start eating.
<br />**3. Data Race**
    <br />When 2 or more threads (philosophers) trying to access a shared resources (fork)
    <br />Solution:
    <br />Mandatory: Mutex
    <br />Bonus: Semaphore

## Threads and Processes 💻
| Thread                                           | Process                                          |
|--------------------------------------------------|--------------------------------------------------|
| Segment of a process                             | Any program is in execution                      |
| Shared memory with its peer threads              | Independent and do not share memory              |
| Shared data segment, code segment, files etc     | Independent data and code segments               |
| Less time for creation and termination           | More time for creation and termination           |
### Functions for thread
**pthread_create**
```
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
```
Start a new thread in the calling process. New thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine().
<br /><br />**pthread_detach**
```
int pthread_detach(pthread_t thread)
```
Marks the thread identified by thread as detached. When a detached thread termiantes, its resources are automatically released back to the system without the need for another thread to join with the terminated thread.
<br /><br />**pthread_join**
```
int pthread_join(pthread_t thread, void **retval)
```
Waits for the thread specified by thread to terminate. If that thread has already terminated, pthread_join returns immediately.

### Functions for process:
**fork**
```
pid_t fork()
```
![Fork()](https://user-images.githubusercontent.com/81152890/157390353-e48c0d15-4e66-453a-b9d7-79ce22fa2641.jpeg)
**kill**
```
int kill(pid_t pid, int sig)
```
Send a signal to process or process group specified by pid. Sending SIGKILL signal will kill running process.
**<br /><br />waitpid**
```
pid_t waitpid(pid_t pid, int *status, int options)
```
Wait for a specified child process to end.
- If pid > 0, waitpid() waits for termination of specific child whose process ID == pid.
- If pid == 0, waitpid() waits for termination of any child whose process group ID == caller.
- If pid == -1, waitpid() waits for any child process to end.
- If pid < -1, waitpid() waits for termination of any child whose process group ID == absolute value of pid.


## Mutex :lock:
Locking mechanism used to synchronize access to a resource. Only one philo allowed to access critical section at one time.
In this project, we will need mutex for 3 parts
1. Mutex for each forks
2. Mutex when printing out statement (displayed state message should not mixed up with another message)
3. Mutex between checking the death of philo and when the philo is eating.
    (As we need to access philo's last meal in routine, saving last meal and check_death function by comparing time of last meal and current time)
### Functions
**pthread_mutex_init**
```
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_attr_t *attr)
```
Initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.
<br /><br />**pthread_mutex_destroy**
```
int pthread_mutex_destroy(pthread_mutex_t *mutex)
```
Destroys the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialised. An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value. A destroyed mutex object can be re-initialised using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.
<br /><br />**pthread_mutex_lock**
```
int pthread_mutex_lock(pthread_mutex_t *mutex)
```
Set lock for critical section, so that only one thread allowed to access the locked region of code.
If other thread wants to access critical region, it will be scheduled while thread 1 was not done accessing the shared resources.
<br /><br />**pthread_mutex_unlock**
```
int pthread_mutex_unlock(pthread_mutex_t *mutex)
```
Unlock after using it.
## Semaphore :lock:
Semaphore is simply a varible that is non-negative and shared between threads. A semaphore is a signaling mechanism, and a thread that is waiting on a semaphore can be signaled by another thread. It uses two atomic operations, 1) Wait, and 2) Signal for the process synchronization.
### Functions
**sem_open**
```
sem_t *sem_open(const char *sem_name, int oflag, ...)
```
** parameter "mode_t mode" and "unsigned int value" are optional.
<br />oflags:
- O_CREAT: used to create semphore if it does not already exist.
- O_EXCL: if O_CREAT and O_EXCL are set, sem_open() fails if the semaphore name exists. If O_EXCL is set and O_CREAT is not set, the effect is undefined.

mode: Access permission.
<br />value: Initial value of sempahore. A positive value (i.e. greater than zero) indicates an unlocked semaphore, and a value of 0 (zero) indicates a locked semaphore. 
<br /><br />**sem_close**
```
int sem_close(sem_t *sem)
```
Closes the named semaphore referred to by sem, allowing any resources that the system has allocated to the calling process for this semaphore to be freed.
<br /><br />**sem_post**
```
int sem_post(sem_t *sem)
```
Increments (unlocks) the semaphore pointed to by sem. If the semaphore's value consequently becomes greater than zero, then another process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
<br /><br />**sem_wait**
```
int sem_wait(sem_t *sem)
```
Decrements (locks) the semaphore pointed to by sem. If the semaphore's value is greater than zero, then the decrement proceeds, and the function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.
<br />**sem_unlink**
```
int sem_unlink(const char *name)
```
The sem_unlink() function unlinks a named semaphore. The name of the semaphore is removed from the set of names used by named semaphores. If the semaphore is still in use, the semaphore is not deleted until all processes using the semaphore have ended or have called sem_close(). Using the name of an unlinked semaphore in subsequent calls to sem_open() or sem_open_np() will result in the creation of a new semaphore with the same name if the O_CREAT flag of the oflag parameter has been set.

### References :paperclip:
1. Short Intro to Threads (Playlist by CodeVault): https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2 
2. Difference between processes and threads: https://www.youtube.com/watch?v=IKG1P4rgm54
3. Deadlock: https://www.youtube.com/watch?v=oq29KUy29iQ
4. Dining Philosophers: http://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html
5. Solving Dining Philosophers by Mutex: https://www.youtube.com/watch?v=oq29KUy29iQ
6. Solving Dining Philosophers by Semaphore: https://medium.com/swlh/the-dining-philosophers-problem-solution-in-c-90e2593f64e8
7. Waitpid: https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-waitpid-wait-specific-child-process-end
8. Thread Synchronization: https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
9. sem_open: http://www.qnx.com/developers/docs/qnxcar2/index.jsp?topic=%2Fcom.qnx.doc.neutrino.lib_ref%2Ftopic%2Fs%2Fsem_open.html
10. Difference between mutex and semaphore: https://afteracademy.com/blog/difference-between-mutex-and-semaphore-in-operating-system#:~:text=A%20mutex%20object%20allows%20multiple,same%20process%20at%20a%20time. 
