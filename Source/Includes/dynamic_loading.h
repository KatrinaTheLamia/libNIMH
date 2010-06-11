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
 */

#ifdef __LIBNIMH_DYNAMIC_LOADER__
#define __LIBNIMH_DYNAMIC_LOADER__

typedef void * nimh_library_payload;
typedef unsigned char nimh_module_mode;

typedef struct {
	nimh_id internal;
	nimh_string callable_name. library_path;
	nimh_library_payload payload;
	nimh_module_mode my_mode;
	void *NEXT;
	void *PREV;
} nimh_module_data nimh_module;

void load_nimh_mod(nimh_book*,nimh_string*,nimh_string*, nimh_module_mode);
void unload_nimh_mod(nimh_book*,nimh_string*);
void reload_nimh_module(nimh_book*,nimh_string*);
bool nimh_mod_loaded(nimh_book*, nimh_string*);
bool nimh_mod_name_exists(nimh_book*, nimh_string*);
void loader_thread_error(nimh_book*);

#endif // __LIBNIMH_DYNAMIC_LOADER__
