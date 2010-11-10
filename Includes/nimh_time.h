/* nimh-doc
 * = %(libNIMH-Includes)path/nimh_time.h
 * @Author : %(KatrinaTheLamia)user
 * @Groups : %(NIMHLabs)group %(SpectrumLabs)group
 * @Projects : %(libNIMH)project
 * @Creation : 3176-5-22
 * @LICENSE : %(libNIMH-docs)path/LICENSE.TXT
 *
 * A time handling/translation function
 *
 * == Revisions
 * + 3176-5-22 Created this file
 *
 * == TODO
 * ! Implement
 * ! Document/Comment
 * ! Debug
 *
 */


#ifndef __libNIMH_NIMH_TIME_H__
#define __libNIMH_NIMH_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *ident;
	unsigned float conversion;
	void *NEXT;
	void *PREV;
} nimh_time_varients_dat nimh_time_varients;

typedef struct {
	unsigned long long timestamp;
	bool is_real_time;
	char *ident;
	nimh_time_varient *modification;
} nimh_time_dat nimh_time;

typedef struct {
	char *ident;
	unsigned long long day;
	unsigned long annuam_chunk;
	unsigned long annuam_length;
	unsigned short day_straight;
	unsigned short years_to_mod;
	unsigned float year_inaccuracy;
	unsigned long day_chunk*;
} nimh_calender_dat nimh_calender;

typedef struct {
	char *ident;
	nimh_time *a, *b;
	unsigned long long cached_diff;
} nimh_time_diff_dat nimh_time_diff;

typedef unsigned long long time*;
typedef unsigned short date*;

nime_time* nime_time(char*);
unsigned long long convert_quanta(nimh_time*);
bool attach_converstion(nimh_time*,nimh_time_varients*);
bool apply_timestamp(nimh_time*);
bool set_inaccuracy(nimh_time*);
bool set_accurate(nimh_time*);
bool is_accurate(nimh_time*);

nimh_time_varients *nimh_time_varient(nimh_time_varients, char*, float);
bool mod_varient(nimh_time_varients, char*, float);

nimh_calender* nimh_calender(char *, unsigned long long, unsigned long, unsigned long, unsigned short, unsigned short);
bool leap_year_mod(nimh_calender *, unsigned float, unsigned short);
time my_time(nimh_time*,nimh_calender*);
date my_date(nimh_time*,nimh_calender*);

nimh_time_diff* nimh_time_diff(char *, nimh_time*,nimh_time*);
unsigned long long calculate(nimh_time_diff*);

time calender_convert(nimh_time*,nimh_calender*,nimh_calender*);
date calender_convert(nimh_time*,nimh_calender*,nimh_calender*);

#ifdef __cplusplus
};
#endif

#endif /* Hammer... er... NIMH TIME! */
