/*nimh-doc
 *= %(libNIMH-Includes)path/storage.h
 * Author: %(KatrinaTheLamia)user
 * Groups: %(NIMHLabs)group %(TeamTemporal)group %(RaddTeam)group 
 *         %(MonsterAcademy)
 * Project: %(libNIMH)project
 * License: %(libNIMH-Documentation)path/LICENSE.txt
 * Creation: 3176-4-41
 *
 * Storage information for libNIMH application
 *
 *== Revisions
 * + 3176-4-41 Created file
 * + 3176-4-42 Moved Read and Write operations to function pointers
 *== TODO
 * ! Complete file
 * ! Documentation
 * ! Debug
 */

#ifndef __NIMH_STORAGE_H__
#define __NIMH_STORAGE_H__

#if __cplusplus
extern "C" {
#endif /* guards for other languages */

typedef (void)(file_handling_duty*)(void*,nimh_string*,nimh_string*);

typedef struct {
    nimh_widget __parent;
    nimh_time flush_rate;
    nimh_netspeed throttle;
    nimh_string driver_string;
    void *driver_data;
    file_handling_duty *read, *write, *open, *close, *flush, *my_lock, *my_unlock;
} nimh_file_handle_data nimh_file_handle;

/*=== Functions
 */
/*==== create_storage
 * Param: nimh_book: my book
 * Param: nimh_string: storage name
 * Param: nimh_string: driver identification
 * Return: nothing
 * Notes: Side effect function
 *
 * Create a new storage item, and run it with its specific driver
 *
 */
void create_storage(nimh_book*,nimh_string*,nimh_string*);

void lock(nimh_book*,nimh_string*);
void unlock(nimh_book*,nimh_string*);

void flush_all(nimh_book*);

void check_handle(nimh_book*,nimh_string*);

#if __cplusplus
};
#endif /* end guards */
#endif /* __NIMH_STORAGE_H__ */
