/*nimh-doc
 * File: %(libNIMH-source)path/dynamic_loading_linux.c
 * Author: %(KatrinaTheLamai)user
 * Groups: %(NIMHLabs)group, %(RaddTeam)group
 * Projects: %(libNIMh)project
 * Creation: 3176-3-14
 *
 * This is for implementing the dynamic loading system on linux systems
 * If you want to compile the loading system on windows. Check out
 * dynamic_loading_win.c
 *
 * Typically, this switch should be made, in the make file, or project
 * file. Rather than in C source.
 *
 *== Revisions
 * + 3176-3-14 creation file initially
 */

/*
 * Yeah, this SHOULD work on BSD too. May need to add a cludgel for OSX.
 *
 * Though, nothing works on Solaris, so not expecting it.
 *
 * Not certain if Amiga OS had Dynamic Loading >.>'
 */
#ifdef USE_LINUX

#include <dlfcn.h>

void *load_nimh_mod(nimh_book *my_book, nimh_string *friendly, nimh_string *path, nimh_module_mode my_mode) {
	nimh_string info = nimh_cached_token(my_book, "EN-CA", "Information Log");
	nimh_string warn = nimh_cached_token(my_book, "EN-CA", "Warning Log");
	nimh_string loader_error_thread = nimh_cache_token(my_book, "EN-Ca", "Module Loader Error Thread");
	nimh_modile *curr, *head = my_book->modules;
	curr = head;

	if(nimh_mod_loaded(my_book, path)) {
		nimh_error(my_book, "EN-Ca", "module aleady loading. Leaving");
		return;
	}

	if(nimh_mod_name_exists(my_book, friendly)) {
		nimh_error(my_book, "EN-Ca", "module friendly name exists. Try Unloading it first");
		return;
	}


	if(!(my_mode & RTLD_NOW || my_mode & RTLD_LAZY)) {
		nimh_log(my_book, info, nimh_string(my_book, "EN-Ca", "No proper mode given for module load. Lazy load for lazy coder."));
		my_mode |= RTLD_LAZY;
	} else if(my_mode & RTLD_NOW) {
		nimh_log(my_book, info, nimh_string(my_book, "EN-Ca", "Loading Module, now! We cannot wait!"));
	} else if(my_mode & RTLD_LAZY) {
		nimh_log(my_book, info, nimh_string(my_book, "EN-Ca", "Lazing module load. Will stop procrastinating tommorrow."));
	} else {
		nimh_error(my_book, "EN-CA", "We are in a section of code we should not be.");
		return;
	}
	if(my_mode & RTLD_LOCAL) {
		nimh_log(my_book, warn, nimh_string(my_book, "EN-Ca", "You appear to be trying to run module in local. This module will not see libNIMH data"));
		nimh_log(my_book, warn, nimh_string(my_book, "EN-Ca", "This concept makes no sense. If you want to segregate data, Just us a different nimh_book"));
		nimh_log(my_book, warn, nimh_string(my_book, "EN-Ca", "Switching to a global mode. In the future, segregate data between books."));
		my_mode ^= RTLD_LOCAL;
		my_mode |= RTLD_GLOBAL;
	} else if(!my_mode & RTLD_GLOBAL) {
		nimh_log(my_book, info, my_string(my_book, "EN-Ca", "No access mode given. Swtiching to Global loading"));
		my_mode |= RTLD_GLOBAL;
	} else if(my_mode & RTLD_GLOBAL) {
		nimh_log(my_book, info, nimh_string(my_book, "EN-Ca". "Loading in global mode."));
	} else {
		nimh_error(my_book, "EN-CA", "We are in a section of code we should not be in");
		return;
	}


	if(!nimh_thread_running(loader_thread_error)) {
		nimh_start_thread(nimh_book, loader_thread_error, nimh_dynaload_error, nil);
	}

	nimh_module *new_module = malloc(size_of(nimh_module_data));

	new_module->payload = dlopen(path, my_mode);
        new_module->callable_name = friendly;

	while(curr->NEXT != nil) {
		curr = head->NEXT
	}

	curr->NEXT = new_module;
	return;
}

void unload_nimh_mod(nimh_book *my_book, nimh_string *Friendly) {
	nimh_string warn = nimh_string("EN-Ca","Warning Log");
	nimh_module *curr = my_book->modules->NEXT;

	while(curr != nil && not nimh_string_equals(curr->friendly, Friendly)) {
		curr = curr->NEXT;
	}

	if(curr == nil) {
		nimh_log(my_book, warn, nimh_string("EN-Ca", "Friendly name does not match a module loaded. Did you typo?"));
	}

	dlclose(curr->payload);

	curr->PREV->NEXT = curr->Next;
	curr->PREV = nil;
	curr->NEXT = nil;

	free(curr);

}


#endif // USE_LINUX
