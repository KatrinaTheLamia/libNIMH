/*nimh-doc
 * File : %(libNIMHsource-root)path/memory_management.h
 * Project : %(libNIMH)project
 * Authors : %(KatrinaTheLamia)author
 * Groups : %(NIMHLabs)group
 * Licenses : %(libNIMHdocs-root)path/LICENSE.txt
 * Created on : 3176-1-02
 * Revisions :
 * 3176-1-02 + created this file
 * TODO :
 * * Properly code and finish this.
 * * In data type files... set NIMH Libs word to default to 64bit... making 
 *   provisions for 32bit systems. In the case of a 16bit system, the word 
 *   will default to 8bit. I really see not much of a chance of using systems 
 *   that have 7bit, 9bit, 6bit, 5bit or 4bit words any time soon though--
 *   so code will not be implement for that... however, options for it will
 *   be put in for future setups.
 * Purpose:
 * A general purpose memory management object for use in various NIMH Labs
 * projects, as well projects that makes use of the Libraries of NIMH.
 */

#include <config.h>

#include <types.h>

#ifndef __libNIMH_Memory_Management_H__
#define __libNIMH_Memory_Management_H__

/*nimh-doc
 * Data Structure : nimh_book
 * Member : nimh_string : application_name : localised name for the application
 * Member : nimh_pids : pids : Pids associated to the current program.
 * Member : nimh_stack : stack : this book's data stack (short term memory)
 * Member : nimh_sockets : sockets : this programs socket data.
 * Member : nimh_threads : threads : this programs thread data.
 * Member : nimh_configuration : configuration : this programs configuration data
 * Member : nimh_storage : storage : Storage information for this program.
 * Member : nimh_datas : data : various data information for this program.
 */
typedef struct {
    nimh_string *application_name;
    nimh_pids pids;
    nimh_stack stack;
    nimh_sockets sockets;
    nimh_threads threads;
    nimh_configure configuration;
    nimh_storage storage;
    nimh_datas data;
} nimh_book_data nimh_book;

typedef struct {
    nimh_string *data_entry;
    nimh_data *payload;
    void *PREV;
    void *NEXT;
} nimh_datas_data nimh_data;

/*nimh-doc
 * Function : application
 * Param : nimh_book : should be a NIMH book--if nil, will create a new 
 * NIMH Book.
 * Param : nimh_string : application name--set up in a localised method.
 * Param : nimh_args : the arguments given to this program.
 * Return : nimh_book : created application
 * Purpose:
 * Construct a new lib NIMH application.
 */
nimh_book* application(nimh_book*,nimh_string*,nimh_args*);

/*nimh-doc
 * Function : pop
 * Param : nimh_book : NIMH application being dealt with
 * Return : nimh_word : stack element
 * Purpose : stack
 * Function : shift
 * Param : nimh_book : NIMH application being dealt with
 * Return : nimh_work : stack element
 * Purpose : stack
 * Function : push
 * Param : nimh_book : NIMH application being dealt with
 * Param : nimh_word : stack data
 * Return : nimh_book : NIMH application being dealt with
 * Purpose : stack
 * Function : unshift
 * Param : nimh_book : NIMH application
 * Param : nimh_word : stack data
 * Return : nimh_book : NIMH application being dealt with
 * Purpose :
 * Talk to the NIMH Application Stack. Generally will return the system word 
 * for this application. 
 *
 * I hope that the functions "pop", "push", "shift" and "unshift" really have 
 * no requirements to be explained here.
 */
nimh_word* pop(nimh_book*);
nimh_word* shift(nimh_book*);
nimh_book* push(nimh_book*,nimh_word*);
nimh_book* unshift(nimh_book*,nimh_word*);

/*nimh-doc
 * Function : _socket
 * Param : nimh_book : NIMH application being dealt with.
 * Param : nimh_string : socket we desire to talk to.
 * Private : This function is for internal use in libNIMH
 * Return : nimh_socket : the socket requested
 * Purpose : grab a socket for the purpose of talking to it.
 * Notes : functions for creating and dealing with sockets are defined 
 * elsewhere.
 */
nimh_socket* _socket(nimh_book*,nimh_string*);

/*nimh-doc
 * Function : _thread
 * Param : nimh_book : NIMH application being dealt with.
 * Param : nimh_string : thread we desire to talk to.
 * Private : This function is for internal use in libNIMH.
 * Return : nimh_thread : the thread requested
 * Purpose : grab a thread for talking to.
 * Notes : functions for exact usage with nimh threads are defined
 * elsewhere
 */
nimh_thread* _thread(nimh_book*,nimh_string*);

/*nimh-doc
 * Function : _config
 * Param : nimh_book : NIMH application being dealt with.
 * Param : nimh_string : the configurtion information we desire.
 * Private : This function is for internal use in libNIMH
 * Return : nimh_data : generic libNIMH configuration data.
 * Purpose : for dealing with information that changes how the program works
 * and operates. Any data that changes how we work, should be put into this 
 * data area.
 * Notes : functions for the exact usage of this configuration are defined 
 * elsewhere.
 */
nimh_data* _config(nimh_book*,nimh_string*);

/*nimh-doc
 * Function : data
 * Param : nimh_book : NIMH application being dealt with.
 * Param : nimh_string : name of the data we want to talk to.
 * Param : nimh_data : nil : data to be put into the program.
 * Return : nimh_data : data being dealt with.
 * Return : nimh_book : NIMH application being dealt with/
 * Purpose :
 * Basic libNIMH heap. Makes it easier to track it within a libNIMH 
 * application if we do it like this.
 */
nimh_data* data(nimh_book*,nimh_string*,nimh_data*=nil);
nimh_book* data(nimh_book*,nimh_string*,nimh_data*=nil);


#endif /* __libNIMH_Memory_Managament_H__ */
