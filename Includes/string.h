/*nimh-doc
 *= %(libNIMH-Includes)path/nimh_string.h
 * Author: %(KatrinaTheLamia)user
 * Project: %(libNIMH)project
 * Groups: %(NIMHLabs)group %(RaddTeam)group %(TeamTemporal)group
 *         %(MonsterAcademy)group %(SpectrumLabs)group
 * Licenses: %(libNIMH-Documentation)path/LICENSES.txt
 * Creation: 3176-4-52
 *
 *== Revisions
 * + 3176-4-52 Created fire
 *
 *== TODO
 *
 * ! 3176-4-52 Need to comment more
 *
 */


#ifndef __libNIMH_TIME_H__
#define __libNIMH_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int langauge_instance;
    char *locale;
    char *content;
    bool stale;
} nimh_string_dat, nimh_string;

nimh_string* nimh_string(nimh_book *, char *, char *);

/* nimh_token is pretty much the same */
#define nimh_token(x, y, z) nimh_string(x, y, z)

nimh_string* has_token(nimh_book *, char *, char *);

int nimh_match(nimh_book *, nimh_string *, nimh_regex *);
int nimh_replace(nimh_book *, nimh_string *, nimh_regex *, nimh_string);
int nimh_replace(nimh_book *, nimh_string *, nimh_regex *, nimh_regex);
int nimh_had_match(nimh_book *, nimh_string *, nimh_regex *);

bool nimh_equal(nimh_book *, nimh_string *, nimh_string *);
bool nimh_equal(nimh_book *, nimh_string *, nimh_regex *);

void change_locale(nimh_book *, char *);

#ifdef __cplusplus
};
#endif
#endif /* end __libNIMH_TIME_H__ */
