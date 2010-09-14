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
 * + 3176-3-15 defined the last prototypes required
 * + 3176-3-15 Comments.. now... WITH FEELING
 * ~ 3176-3-15 Syntax error in loader... yeah.. fixed that
 * ~ 3176-3-15 fixed issue with pointer math in definition
 * + 3176-3-15 oh, hey--that error monitor function... right...
 * + 3176-3-15 shutdown sequence added
 * ~ 3176-3-15 Right... forgot. C does not automatically fix typing issues.
 * ~ 3176-3-15 seeking issues fixed
 * ! 3166-4-38 File broken by header file change see todo
 *
 *== TODO
 * 3176-3-15 ? look into a definition file that is target library neutral
 * 3176-3-15 ? translate error letters into meaningful messages
 * 3176-4-38 ! Broken, add support for nimh widget to support head
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

/*== Linux Defintions
 * Various prototypes in header files getting defined here.
 */

/*nimh-doc
 *=== void load_nimh_mod(nimh_book*, nimh_string *, nimh_string *, nimh_module_mode)
 *
 */
void load_nimh_mod(nimh_book *my_book, nimh_string *friendly, nimh_string *path, nimh_module_mode my_mode) {
	/*
 	 * Grab the various string tokens we need, to make this program run a little less sluggish 
 	 */
	nimh_string info = nimh_cached_token(my_book, "EN-CA", "Information Log");
	nimh_string warn = nimh_cached_token(my_book, "EN-CA", "Warning Log");
	nimh_string loader_error_thread = nimh_cache_token(my_book, "EN-Ca", "Module Loader Error Thread");

	/*
 	 * Grab our first module. The "HEAD" module is empty... this is to simplify code.
 	 */
	nimh_modile *curr = (nimh_module*) my_book->modules->NEXT;

	/*
 	 * As much as we love conflict--computers will have issues by it. Making certain that neither
 	 * the module path is loaded--nor is the friendly name used.
 	 *
 	 * Also note: it IS possible for modules to conflict with each other when loaded this way. Just
 	 * as if they were compiled as a nonNIMH application.
 	 */
	if(nimh_mod_loaded(my_book, path)) {
		nimh_error(my_book, "EN-Ca", "module aleady loading. Leaving");
		return;
	}

	if(nimh_mod_name_exists(my_book, friendly)) {
		nimh_error(my_book, "EN-Ca", "module friendly name exists. Try Unloading it first");
		return;
	}


	/*
 	 * Now--our module modes, are they in order.
 	 * This can be passed with no modes, and you will get a Lazy Load.
 	 *
 	 * Due to how libNIMH is suppose to function... it does not make sense to 
 	 * load them as LOCAL. If you want it to not conflict, you can load it 
 	 * into its own book.
 	 *
 	 * Though, this is not to say that libNIMH aware modules could not 
 	 * look into other books. This would require them knowing name of the 
 	 * module to talk with. Typically, you code should understand that its 
 	 * input may be complete garbage.
 	 *
 	 * Note to self: add forked_book into the libNIMH setup >.>'
 	 */ 
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

	/*
 	 * Start the thread dedicated to seeing if the loader has screwed up
 	 */
	if(!nimh_thread_running(loader_thread_error)) {
		nimh_start_thread(nimh_book, loader_thread_error, nimh_dynaload_error, nil);
	}

	/*
 	 * Now then, let us create our new module
 	 */
	nimh_module *new_module = (nimh_mdoule *) malloc(size_of(nimh_module_data));

	new_module->payload = dlopen(path->contents, my_mode);
        new_module->callable_name = friendly;
	new_module->library_path = path;
	new_module->my_mode = my_mode;

	/*
 	 * Grab the location to put it and put it there.
 	 */
	while(curr->NEXT != nil) {
		curr = (nimh_module*) curr->NEXT
	}
	curr->NEXT = (void*) new_module;
}

/*
 * === void unload_nimh_mod(nimh_book*,nimh_string*);
 */
void unload_nimh_mod(nimh_book *my_book, nimh_string *Friendly) {
	/*
 	 * grab out string token, as well as our first module
 	 */
	nimh_string warn = nimh_cached_token("EN-Ca","Warning Log");
	nimh_module *curr = (nimh_module*) my_book->modules->NEXT;

	/*
 	 * Try to locate a module with this friendly name
 	 */
	while(curr->NEXT != nil && not nimh_string_equals(curr->friendly, Friendly)) {
		curr = (nimh_module*) curr->NEXT;
	}

	/*
 	 * If we did not find the name, bugger out of here.
 	 */
	if(curr == nil) {
		nimh_log(my_book, warn, nimh_string("EN-Ca", "Friendly name does not match a module loaded. Did you typo?"));
		return;
	}

	/*
 	 * other wish, close the file handle, link the linked list in the 
 	 * proper fashion, and delete the node.
 	 */
	dlclose(curr->payload);

	curr->PREV->NEXT = curr->NEXT;
	curr->PREV = nil;
	curr->NEXT = nil;

	free(curr);
	curr = nil;
}

/*
 *=== void reload_nimh_mod(nimh_book*,nimh_string*)
 */
void reload_nimh_mod(nimh_book *my_book, nimh_string *friendly) {

	/*
	 * Grab first module, an allocate a temporary module into memory.
	 * The temp module is only to hold meta data.
	 *
	 * Right--and we have a nimh_string that we request the stored
	 * form of.
	 */
	nimh_module *curr = (nimh_module*) my_book->modules->NEXT;
	nimh_module *meta_module = (nimh_module*) malloc(size_of(nimh_module_data));

	nimh_string *info = nimh_cached_token("EN-Ca","Information Log");

	/*
 	 * Does this friendly name point to anything?
 	 *
 	 * If not, we really do not need to do much more than alert to the
 	 * user that the module has not been loaded.
 	 */
	if(not nimh_mod_name_exists(my_book, friendly)) {
		nimh_error(my_book, info, nimh_string(my_book,"EN-Ca","module does not appear to be loaded"));
		return;
	}

	/*
 	 * Let us grab our module....
 	 */
	while(curr->NEXT != nil && not nimh_string_equals(curr->friendly, friendly)) {
		curr = (nimh_module*) curr->NEXT;
	}

	/*
 	 * Grab its key information... 
 	 */
	meta_module->friendly = friendly;
	meta_module->path = curr->path;
	meta_module->my_modes = curr->modes;

	/*
 	 * Unload the module
 	 */
	unload_nimh_mod(my_book,friendly);

	/*
 	 * Load the new version
 	 */
	load_nimh_mod(my_book,meta_module->friendly,meta_module->path,meta_module->my_modes);

	/*
 	 * Guess what? This meta information is no longer needed!
 	 */
	free(meta_module);
	meta_module = nil;
}

/*
 *=== bool nimh_mod_loaded(nimh_book, nimh_string)
 *
 * Hey! Does this file handle exist in our loader?
 *
 */

bool nimh_mod_loaded(nimh_book *my_book, nimh_string *module_path) {
	nimh_module *curr = (nimh_module*) my_book->modules->NEXT;

	while(curr != nil) {
		if(nimh_string_equals(curr->library_path, module_path)) {
			return true;
		}
		curr = (nimh_module*) curr->NEXT;
	}
	return false;
}

/*
 *=== bool nimh_mod_name_exists(nimh_book, nimh_string)
 * Do we have this friendly name here?
 *
 * TODO: Look into making a system independant defintion file.
 */
bool nimh_mod_name_exists(nimh_book *my_boo, nimh_string *friendly_name) {
	nimh_module *curr = (nimh_module*) my_book->modules->NEXT;

	while(curr != nil) {
		if(nimh_string_equals(curr->friendly, friendly_name)) {
			return true;
		}
		curr = (nimh_module*) curr->NEXT;
	}
	return false;
}

/*
 *=== void loader_thread_errer(void*)
 */
void loader_thread_error(void *my_void_book) {
	/*
 	 * right-- get our book into the right type
 	 */
	nimh_book *my_book = (nimh_book*) my_void_book;

	/*
 	 * our error character; 
 	 */
	char *error;	

	/*
 	 * just poll if there is an error.
 	 */
	while(*my_book->open) {
		if((error = dlerror()) != nil) {
			nimh_error("C",sprintf("Dynamic_loader error: %s",error));
		}
		nimh_thread_rest(low_priority);
	}
}

/*
 *=== void mod_shutdown(nimh_book*)
 */
void mod_shutdown(nimh_book *my_book) {
	nimh_module *curr = (nimh_module*) my_book->modules->NEXT;
	nimh_string *shutdown_name;

	/*
 	 * Zoom to the end
 	 */
	while(curr->NEXT != nil) {
		curr = (nimh_module*) curr->NEXT;
	}

	/*
 	 * delete modules in order. 
 	 */
	while(curr->PREV->payload != nil) {
		shutdown_name = curr->friendly;
		curr = (nimh_modules*) curr->PREV;
		unload_nimh_mod(shutdown_name);
	}
}

/*
 * === void init_nimh_modules(nimh_book*)
 */
void init_nimh_modules(nimh_book *my_book) {
	/*
 	 * hey?! Are we already initialised?
 	 */
	if(nil != my_book->modules || nil != my_book->modules->NEXT) {
		nimh_error("EN-Ca","We already have a module set up");
		return 0;
	}

	/*
 	 * If not, the head module should just be an empty thing. 
   	 */
	my_book->modules = (nimh_module *) malloc(size_of(nimh_module_data));

	my_book->modules->PREV = nil;
	my_book->modules->NEXT = nil;
	my_book->modules->payload = nil;
}

#endif // USE_LINUX
