/*nimh-doc
 * File: %(libNIMH-Includes)path/dynamic_loader.h
 * Author: %(KatrinaTheLamia)user
 * Group: %(NIMHlabs)group, %(Radd Team)group
 * Creation Date: 3176-3-14
 *
 * The Dynamic Loader is a part of the libNIMH framework that controls 
 * and keeps track of what has been loaded... and what has not. As 
 * well as the option to unload a module, reload and what not.
 *
 * There is the option to allow the program making use of libNIMH 
 * have entry points in the modules loaded into here.
 *
 * Modules, should be your typical linux shared objects, or your
 * typical windows shared objects.
 *
 * There are also hopes to add time out options for unresponsive, or 
 * bulky libraries loaded into libNIMH. As while the OS could do that 
 * itself (how?), if we forked out loading. It just makes more sense 
 * to internalise how and what we are doing here.
 *
 * This is being added into libNIMH, because the idea of doing this 
 * does not appear often enough in code.
 *
 * And since libNIMH hopes to simplify the use of sockets and threads,
 * this may as well, also be added.
 *
 *== Revisions
 * + 3176-3-14 Created this header file.
 * + 3176-3-15 Added required parts
 * + 3176-3-15 Commented this... though not with as much feeling as I'd hope
 * ~ 3176-3-15 Right... we should uh... you know, follow our threading systems
 *             Just saying..
 * + 3176-3-15 added shutdown sequence
 * + 3176-3-15 added initialiser
 * ~ 3176-4-38 fitting it to use the libNIMH widgetting system
 *
 *== TODO
 * 3176-3-15 ? libNIMH tracker type? Something to contain the nimh_id
 * PREV, NEXT and anything else our schevy little mind desires?
 */

#ifdef __LIBNIMH_DYNAMIC_LOADER__
#define __LIBNIMH_DYNAMIC_LOADER__

/*
 *== Types
 *=== nimh_library_payload
 *
 * A type that is mean to contain the payload that an added module gives.
 *
 *=== nimh_module_mode
 *
 * Due to ambiguity as to how windows modes will work, we will go with a 
 * char for now.
 *
 * Will look into an libNIMH specifi enum in the future
 */

typedef void * nimh_library_payload;
typedef unsigned char nimh_module_mode;

/*=== Objects
 *==== nimh_module
 * Field: internal : nimh_id : just something I will be adding into objects in 
 *                   thid library. It is a place holder for future 
 *                   functionality
 * Field: callable_name : nimh_string : a human readable name to look for this 
 *                                      module
 * Field: library_path : nimh_string : the path of which this module can be 
 *                                     found.
 * Field: payload : nimh_library_payload : the library loaded itself. 
 *                                         Typically a file handle
 * Field: NEXT, PREV : nimh_module (void cast) : linked list items
 *
 * this is a framework to load and unload modules in and out of memory as
 * needed. So as to not require everything staticly linked, or dynamically 
 * linked from the start.
 */
typedef struct {
        nimh_widget __parent;
	nimh_string callable_name. library_path;
	nimh_library_payload payload;
	nimh_module_mode my_mode;
} nimh_module_data nimh_module;

/*===== Methods
 *====== load_nimh_mod
 * Param: nimh_book: our book
 * Param: nimh_string: the name this module will be asked by
 * Param: nimh_module_mode: this module's modes
 * Return: nothing
 *
 * This loads the module. Will put something into the error 
 * spots of memory, should it not work.
 */

void load_nimh_mod(nimh_book*,nimh_string*,nimh_string*, nimh_module_mode);

/*====== unload_nimh_mod
 * Param: nimh_book: our book
 * Param: nimh_string:a friendly human readable name.
 * Return: nothing
 * 
 * This unloads a module.
 *
 * Errors go into the error buffer
 */
void unload_nimh_mod(nimh_book*,nimh_string*);

/*====== reload_nimh_mod
 * Param: nimh_book: our book
 * Param: nimh_string: a friendly human readable identifier
 * Returns: nothing
 *
 * Reloads our module.
 *
 * Errors, again, go on the error buffer
 */

void reload_nimh_module(nimh_book*,nimh_string*);

/*======= nimh_mod_loaded
 * Param: nimh_book: our book
 * Param: nimh_string: the module path
 * Returns: true if loaded. False if not loaded
 *
 * Just a quick check up.
 */
bool nimh_mod_loaded(nimh_book*, nimh_string*);

/*====== nimh_mod_name_exists
 * Param: nimh_book: our book
 * Param: nimh_string: a human readable name
 * Returns: true if name used. False if not
 *
 * A quick check to see if the name has been used.
 */
bool nimh_mod_name_exists(nimh_book*, nimh_string*);

/*====== loader_thread_error
 * Param: nimh_book: our book
 * Returns: nothing... like a good threading function should
 *
 * Just something to poll if what we are wrapping has noted any issues.
 */
void loader_thread_error(void*);

/*====== mod_shutdown
 * Param: nimh_book: our book
 * Returns: nothing... it is a shutdown operation
 *
 * unloads all modules currently loaded in the book
 */
void mod_shutdown(nimh_book*);

/*====== init_nimh_modules
 * Param: nimh_book: our book
 * Returns: nothing
 *
 * Oh hey, starts up our whole mdoule system
 */
void init_nimh_modules(nimh_book*);

#endif // __LIBNIMH_DYNAMIC_LOADER__
