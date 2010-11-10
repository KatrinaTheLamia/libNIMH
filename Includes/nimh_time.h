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
 * This function is not Sirius Bias. Nor is it bias on the Summarian, Chinese,
 * Hebraic, Aztec, Greek or Gregorian Calenders. And, it allows for a variable
 * to correct the timestamp measurement, should it any way be off of what it
 * should.
 *
 * In short--this time routine is simple elegant, and interplanetary travel 
 * ready. Can any other frameworks say that about their time handling?
 *
 * == Revisions
 * + 3176-5-22 Created this file
 * + 3176-5-22 Added placeholder function to adjust conversion based on velocity
 * + 3176-5-22 Added a velocity variable as a placeholder to the nimh_time_varient
 *
 * == TODO
 * ! Implement
 * ! Document/Comment
 * ! Debug
 * ! Get an exact velocity/time adjust formula to use here
 *
 */


#ifndef __libNIMH_NIMH_TIME_H__
#define __libNIMH_NIMH_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *ident;
	unsigned float velocity, conversion;
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

bool recalculate_conversion_for_speed(time_varients*);

#ifdef __cplusplus
};
#endif

#endif /* Hammer... er... NIMH TIME! */
