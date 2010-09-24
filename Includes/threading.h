/*nimh-doc
 *= %(libNIMH-Includes)path/threading.h
 * Author: %(KatrinaTheLamia)user
 * Groups: %(NIMHLabs)group %(TeamTemporal)group
 * Project: %(libNIMH)project
 * Creation: 3176-3-51
 *
 * This is the NIMH Library for messing with NIMH Threading.
 *
 *== Revisions
 * + 3176-3-51 File created
 * + 3176-3-52 Added more function prototypes
 * ~ 3176-4-45 Fixed an empty parenthesis error
 * + 3176-4-47 Commented
 * + 3176-4-47 Better signal functions
 * + 3176-4-47 Sleep and wake up
 *
 *== TODO
 * ! 3176-3-51 Finish coding
 * ! 3176-3-52 Get a more competent attribute system.
 * n.n 3176-4-47 Proper commented this crap
 * ! 3176-3-51 Document
 * ! 3176-3-51 Fix bugs
 * ! 3176-4-47 create nimh time functionality
 */

#ifndef __libNIMH_Threading_H__
#define __libNIMH_Threading_H__

#ifdef __cplusplus
extern "c" {
#endif

/*
 * Yeah--need to make this into more of a call back in future versions of the
 * code set.
 */
/*
 *== Types
 *
 *=== void nimh_thread_func(void*)
 *
 * This is a function pointer. You assign is a function that returns 
 * void and takes a single void pointer argument.
 */
typedef (void)(nimh_thread_func)(void *);

/*
 *== Objects
 */

/*
 *=== nimh_thread
 * Field: __parent: nimh_widget: this is the parent widget to this type
 * Field: tid: unsinged long long: the thread id
 * Field: data_stack: nimh_stack: the thread data stack
 * Field: _scope: nimh_data: Data that is only in scope in this thread. Yes
 *    others can see it.. but this is mostly to allow an abstract location
 *    for it
 * Field: locks: nimh_named_array: what all does my thread have locks on
 * Field: my_function: this thread's function.
 */
typedef struct {
	nimh_widget *__parent;
        unsigned long long tid;
	nimh_stack *data_stack;
        nimh_data *_scope;
	nimh_named_array *locks;
	nimh_thread_func *my_function;
} nimh_thread_data nimh_thread;

/*
 *==== Methods
 */

/*
 *===== create_thread
 * Param: nimh_book: the current book
 * Param: nimh_string: thread's name
 * Param: nimh_thread_func: the function point to pass in
 * Returns: side effect function
 *
 * Creates a thread for us
 *
 */
void create_thread(nimh_book*,nimh_string*,nimh_thread_func);

/*
 *===== terminate
 * Param: none
 * Returns: none
 * Exceptions: Main_Thread_Issue
 * Assumes we are in a thread. Then ends said thread. If not in a thread
 * it throws a "Main_Thread_Issue"
 */
void terminate(void);
/*
 *===== myself
 * Param: none
 * Returns: unsigned long long
 * Exceptions: Main_Thread_Issue
 * Assumes we are in a thread. Mostly wraps around the thread libraries 
 * "this thread" function. However, we will send something to the warning 
 * log, if we are not in a thread.
 */
unsigned long long myself(void);

/*
 *===== lock
 * Param: nimh_book: this current book
 * Param: nimh_string: the variable to be locking
 * Returns: Side Effect
 * 
 * Locks the given variable name to the current thread we are in.
 *
 * If in the main thread, this means the other threads will likely have no 
 * access to the variable.
 */
void lock(nimh_book*,nimh_string*);

/*===== try_lock
 * Param: nimh_book: this current book
 * Param: nimh_string: the variable to be locking
 * Param: unsigned long: time out
 * Returns: Side Effect
 * Exception: Nonlockable
 *
 * Attempts to lock said variable and keeps trying until a lock is made, or 
 * the time out is reached. If time out is reached, Nonlockable exception is 
 * given.
 */
void try_lock(nimh_book*,nimh_string*,unsigned long);

/*
 *===== unlock
 *
 * Param: nimh_book: this current book
 * Param: nimh_string: the function to unlock
 * Returns: Side Effect
 * Exceptions: Is_Unlocked, Denied
 *
 * Attempts to unlock a function. If denied, it throws a Denied. If it already
 * is unlocked, throws an Is_Unlocked
 */
void unlock(nimh_book*,nimh_string*);

/*
 *===== condition
 * Param: nimh_book: this current book
 * Param: nimh_string: the condition's name
 * Returns: Side Effect
 * Exception: Variable_Exists
 *
 * Creates a condition variable that all threads can talk to and access.
 */
void condition(nimh_book*,nimh_string*);

/*
 *===== give_signal
 * Param: nimh_book: this current book
 * Param: nimh_string: condition name
 * Param: void pointer: signal to send to condition
 * Returns: Side Effect function, sends signal to condition
 *
 * Sets signal to condition
 */
void give_signal(nimh_book*,nimh_string*, void*);

/*
 *===== get_signal
 * Param: nimh_book: this book
 * Param: nimh_string: check for signal
 * Returns: void: signal
 *
 * Checks for signal. If signal is not there, nil pointer is return.
 */
void* get_signal(nimh_book*,nimh_string*);

/*
 *===== wait_for_signal
 * Param: nimh_book: this book
 * Param: nimh_string: signal to wait for
 * Param: nimh_time: time out for signal.
 * Returns: void*: signal
 *
 * Wait for signal. If timeout is reached, returns nil pointer
 *
 */

void* wait_for_signal(nimh_book* this_book,nimh_string* signal,nimh_time* timeout=nil);

/*
 *===== nimh_sleep
 * Param: nimh_time: time out for sleep
 * Returns: side effect function
 *
 * Posts a wake up condition, for thread, and sleeps for time.
 */
void nimh_sleep();

/*
 *===== wakeup_polly
 * Param: nimh_book: my book
 * Param: nimh_string: thread to wake up
 * Returns: side effect function
 * Exceptions: Thread_Dead, Thread_Awake
 *
 * Sends a signal to wake up
 */
void wakeup_polly(nimh_book*,nimh_string*);

/* we return to your C++ language */
#ifdef __cplusplus
}
#endif

#endif /* __libNIMH_Threading_H__ */
