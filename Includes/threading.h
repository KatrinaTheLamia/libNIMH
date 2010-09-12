/*nimh-doc
 *= %(libNIMH-Includes)path/threading.h
 * Author: %(KatrinaTheLamia)user
 * Groups: %(NIMHLabs)group %(TeamTemporal)group
 * Project: %(libNIMH)project
 * Creation: 3176-3-51
 *
 * This is 
 *
 *== Revisions
 * ! 3176-3-51 File created
 * + 3176-3-52 Added more function prototypes
 *
 *== TODO
 * ! 3176-3-51 Finish coding
 * ! 3176-3-52 Get a more competent attribute system.
 * ! 3176-3-52 Proper comment this crap
 * ! 3176-3-51 Document
 * ! 3176-3-51 Fix bugs
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
typedef (void)(nimh_thread_func)(void *);

typedef struct {
	nimh_widget *__parent;
	unsigned long long my_id;
	nimh_stack *data_stack;
	nimh_named_array *locks;
	nimh_thread_func *my_function;
} nimh_thread_data nimh_thread;

void create_thread(nimh_book*,nimh_string*,nimh_thread_func);

void terminate();
unsigned long long myself();

void lock(nimh_book*,nimh_string*,nimh_string*);
void try_lock(nimh_book*,nimh_string*,nimh_string*);
void unlock(nimh_book*,nimh_string*,nimh_string*);

void condition(nimh_book*,nimh_string*);
void give_signal(nimh_book*,nimh_string*);
void get_signal(nimh_book*,nimh_string*);




#ifdef __cplusplus
}
#endif

#endif /* __libNIMH_Threading_H__ */
