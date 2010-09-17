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

typedef struct {
    nimh_widget __parent;
    nimh_time flush_rate;
    nimh_netspeed throttle;
    nimh_string driver_string;
    void *driver_data;
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

void write(nimh_book*,nimh_string*,nimh_string*);
void read(nimh_book*,nimh_string*,nimh_string*,nimh_string*);

void lock(nimh_book*,nimh_string*);
void unlock(nimh_book*,nimh_string*);

void flush(nimh_book*,nimh_string*);
void flush_all(nimh_book*);

void open(nimh_book*,nimh_string*,void*);
void close(nimh_book*,nimh_string*);

void check_handle(nimh_book*,nimh_string*);

#if __cplusplus
};
#endif /* end guards */
#endif /* __NIMH_STORAGE_H__ */
