/*nimh-doc
 *= %(libNIMH-includes)path/widget.h
 * Authors : %(KatrinaTheLamia)user
 * Project : %(libNIMH)project
 * Groups : %(NIMHlabs)group %(RaddTeam)group %(TeamTemporal)group
 * Creation: 3176-3-47
 *
 * This file is a standard header file for dealing with libNIMH files. This 
 * is more particularly a base widget type file. This is mostly meant for 
 * keeping track of memory items and objects in a libNIMH file.
 *
 * Since libNIMH is intended to be pure C, this may be a bit more elaborate 
 * than various other language's implementations, like say C++.
 *
 * This allows for us to have our clean up look at this file here for memory
 * management.
 *
 *== Revisions
 * + 3176-3-47 : file creation
 * + 3176-4-42 : Added a simple file lock mechanism
 *== Todo
 * ! Finish file
 * ! Document
 * ! Test
 */

#ifndef __libNIMH_Base_Widget_H__
#define __libNIMH_Base_Widget_H__

/*
 * Include libNIMH's time handling scheme
 */
#include "nimh_time.h"

#ifdef __cplusplus /* C++ check guards*/
Extern "C" {
#endif /* C++ check guards*/

/*nimh-doc
 *== Objects
 * The defintion of objects and structures in this file.
 */

/*nimh-doc
 *=== nimh_widget
 * Field: id: unsigned long long: unique widget id
 * Field: created: nimh_time: time variable was created
 * Field: modified: nimh_time: time variable was last modified
 * Field: read: nimh_tome: time variable was last read
 * Field: access: unsigned long long: access counts
 * Field: flags: unsigned long long: flags used to be able to flip how this
 *               widget is handled.
 * Field: my_mutex: void pointer: for use with locking
 * Field: self: pointer to current "real" variable.
 * Field: prev: widgets are inherently a linked list. Easier that way.
 * Field: next: again, we are dealing with an inherently linked list
 *
 * Common functionality between all objects will be shoved in here with care 
 * willy nilly.
 */
typedef struct {
	unsigned long long id;
	nimh_time created, modified, read;
	unsigned long long access;
	unsigned long long flags;
	void *my_mutex;
	void *self;
	void *prev;
	void *next;
} nimh_widget_data nimh_widget;

/*=== nimh_named_array
 * Field: __parent: the nimh widget that keeps track of us
 * Field: name: entry in this lists "string token"
 * Field: self: the "real" location of our variable
 *
 * Just a basic named linked list set up.
 */
typedef struct {
	nimh_widget *__parent;
	nimh_string *name;
	void *self;
} nimh_named_array_data nimh_named_array;

nimh_widget* nimh_widget();
void destroy(nimh_width*);
void* read(nimh_widget*);
void write(nimh_widget*);
void* previous(nimh_widget*);
void* next(nimh_widget*);
void reap_nodes(nimh_widget*);

nimh_named_array* named_array(nimh_book*,nimh_string*,nimh_named_array);
void destroy(nimh_named_array*);
void *read(nimh_book*,nimh_string*,nimh_string*);
void write(nimh_book*,nimh_string*,nimh_string*,void*);
void remove(nimh_book*,nimh_string*,nimh_string*);

#define prev(x) previous(x);

#ifdef __cplusplus /* Clean up C++ guards*/
}
#endif /* End up C++ Guard clean up */
#endif /* __libNIMH_Base_Widget_H__ */
