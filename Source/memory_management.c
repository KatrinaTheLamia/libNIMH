/*nimh-doc
 * File : %(libNIMH-source-root)path/memory_management.c
 * Projects : %(libNIMH)project
 * Authors : %(KatrinaTheLamia)author
 * License : %(libNIMH-docuementation-root)path/LICENSES.txt
 * Groups : %(NIMHlabs)group
 * Created : 3176-1-03
 * Revisions :
 * + 3176-1-03 created said file
 * ~ 3176-1-35 filled out the last remaining entries into this file
 * TODO :
 * * Properly fill out this file <more or less done>
 * * Properly debug this file
 * * Consider various profiling information we can use for this file.
 * Purpose :
 * This file is to fill in and figure out, how various memory_management.h 
 * type functions are to be done. Most of what we are doing is exceedingly 
 * simplistic in this area. Though--in this version of the file.
 *
 * Likely, once silly things like, say, garbage collection are to be added, 
 * that likely will be done its own file. This file, mostly will include on 
 * stuff for peeking and poking at memory. Creation and destruction will 
 * still use alloc, malloc, calloc and free, like most other C programs. As 
 * there really is no reason to add an entry to the call stack and function 
 * table to deal with that stuff.
 */

/*nimh-doc
 * Include : memory_management.h
 * Purpose :
 * The file we are defining the functions for.
 */
#include <Includes/memory_management.h>

/*nimh-doc
 * Include : configuration.h
 * Purpose :
 * Yeah, we will be using configuration functions in this code. So it is
 * getting included.
 */
#include <Includes/configuration.h>

/*nimh-doc
 * Include : initialisation.h
 * Purpose :
 * Functions in this file are mostly for initialising various functionality 
 * into libNIMH
 */

#include <Includes/initialisation.h>

/*nimh-doc
 * Include : types.h
 * Purpose :
 * types.h is included in Memory_Management.h. This includes the types we 
 * require for this program.
 */

#include <Includes/types.h>

nimh_book* application(nimh_book *my_application, nimh_string *name, nimh_args *commandline_args) {
    if(my_application == nil) {
        my_application = (nimh_book*) malloc(sizeof(nimh_book_dat));
    }
    my_application->application_name = name;
    config(my_application, commandline_args);
    return my_application;
}

nimh_word pop(nimh_book *my_application) {
    nimh_stack_entry *top = my_application->stack;
    nimh_stack_entry *next = top;
    if(not has_init(top)) {
        stack(top);
    }
    if(not is_last(top)) {
        top = top->next;
    }
    while(not is_last(top)) {
        next = top;
        top = top->next;
    }
    if(top == nil) {
        return word_cast(nil);
    }
    nimh_word ret_word = top->payload;
    next->next = nil;
    free(top);
    return ret_work;
}

nimh_word shift(nimh_book *my_application) {
    nimh_word ret_word = my_application->stack->payload;
    if(my_application->stack->next != zero ||
       *my_application->stack->next != nil) {
        nimh_stack_entry *deleted_stack = *my_application->stack->next;
        my_application->stack->payload = deleted_stack->next->payload;
        my_application->stack->next = *deleted_stack->next;
        free(deleted_stack);
    } else {
        my_application->stack->payload = nil;
    }
    return ret_word;
}

nimh_book* push(nimh_book *my_application, nimh_word my_payload) {
    nimh_stack_entry *top = my_application->stack;
    nimh_stack_entry *push = malloc(sizeof(nimh_stack_entry_dat));
    push->payload = my_payload;
    push->next = nil;
    if(top == nil) {
        top = push;
	return my_application;
    }
    while(not is_last(top)) {
       top = top->next;
    }
    top->next = push;
    return my_application;
}

nimh_book* unshift(nimh_book *my_application, nimh_work my_payload) {
    nimh_stack_entry *top = my_application->stack;
    nimh_stack_entry *next = malloc(sizeof(nimh_stack_entry_dat));
    next->payload = top->payload;
    next->next = top->next;
    top->payload = my_payload;
    top->next = next;
    return my_application;
}

nimh_socket* socket(nimh_string *my_application, nimh_string *requested_socket) {
    nimh_word noop;
    nimh_socket *index = my_application->sockets;
    if(not has_init(my_application->sockets)) {
        socket(my_application);
	index = my_application->sockets;
    }
    for(not match(index->name, requested_socket) && not is_last(index); index = (nimh_socket*)index->next) {
        /* currently we will just do a noop of sorts.*/
        noop = 1;
    }
    if(not match(index->name, requested_socket)) {
        signal(my_application, nimh_string("EN-Ca", "Orphan Watch", "Put this data under orphan watch"), (void*)index->next);
        socket(index, requested_socket);
        index = index->next;
    }
    return index;
}

nimh_thread* thread(nimh_string *my_application, nimh_string *requested_thread) {
    nimh_word noop;
    nimh_thread *index = my_application->threads;
    if(not has_init(my_application->threads)) {
        thread(my_application);
        index = my_application->threads;
    }
    for(;not match(index->name, requested_thread) && not is_last(index); index = (nimh_thread*) index->next) {
        /* Yeah, just doing a noop for now. May add some functionality later. */
        noop = 1;
    }
    if(not match(index->name, requested_thread)) {
        signal(my_application, nimh_string("EN-Ca","Orphan Watch","Watch for orphan functions"), (void*)index->next);
        thread(index, request_thread);
        index = (nimh_thread*) index->next;
    }
    return index;
}

nimh_data* data(nimh_book *my_application, nimh_string *requested_data, nimh_data *modification=zero) {
    my_application = data(my_application,requested_data,modification);
    nimh_word noop;
    nimh_data *index = my_application->data;
    if(not has_init(my_application->data)) {
        data(my_application->data);
        index = my_application->data;
    }
    for(;not match(index->name, requested_data) && not is_last(index); index = (nimh_data*) index->next) {
        /* oh right... noop here for now...*/
        noop = 1;
    }
    if(not match(index->name, requested_data)) {
        signal(my_application,nimh_string("EN-Ca","Orphan Watch","Making certain that this data does not get orphaned or anything"),(void*)index->next);
        data(index, request_data, modification);
        index = (nimh_data) index->next;
    }
    return index;
}

void data(nimh_data *target, nimh_string *target_name, nimh_data *initiation=zero) {
    if(not has_init(initiation)) {
        initiation = malloc(sizeof(nimh_datas_data));
        initiation->prev = (void*)target;
        initiation->created = initiation->accessed = now();
        initiation->expries = expires();
    }
    initiation->data_entry = target_name;
    target->next = (void*) initiation;
}

nimh_time expires(nimh_time expires=nil, boolean update=true) {
    static nimh_time ret_val = time_cast(-1);
    if(expires != nil && update == true) {
        ret_val = expires;
    } else if(expires != nil) {
        return expires;
    }
    return ret_val;
}
