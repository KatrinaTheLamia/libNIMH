/*nimh-dic
 *= %(libNIMH-includes)path/configuration.h
 * Author: %(KatrinaTheLamia)user
 * Groups: %(NIMHlabs)group , %(RaddTeam)group , %(TeamTemporal)group ,
 *         %(Misty_of_Hoenn_Monster_Academy)group , %(Virtual_Girl)group
 * License: %(libNIMH-documentation)path/LICENSES.txt
 * Creation: 3176-4-39
 *
 * Configuration is a header file for use with parsing various configuration 
 * options with libNIMH programs. It both runs by loading from a standard 
 * configuration file as well as taking command line arguments to modify the
 * current running configuration.
 *
 *= Revisions
 * + 3176-4-39 Prototype file's creation
 *
 *= TODO
 * ! Document this stuff
 * ! Test this stuff
 */

#ifndef __NIMH_CONFIGURATION_H__
#define __NIMH_CONFIGURATION_H__

#ifdef __cplusplus
extern "C" {
#endif /* C++ guard */

/*
 */

typedef struct {
    nimh_widget *__parent;
    nimh_string *storage_ident;
    nimh_named_array *config_options;
    bool write_change;
} configuration_struct_data configuration_struct;

void update_config(nimh_book* my_book);
nimh_string *config_storage_ident(nimh_book* my_book, nimh_string* path=0);
void config(nimh_book* my_book,nimh_string* key,nimh_string* my_value=0);

#ifdef __cplusplus
};
#endif /* Back to your normal language*/

#endif
