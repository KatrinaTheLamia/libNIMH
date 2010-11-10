/*nimh-doc
 *= %(libNIMH-Includes)path/nimh_string.h
 * @Author: %(KatrinaTheLamia)user
 * @Project: %(libNIMH)project
 * @Groups: %(NIMHLabs)group %(RaddTeam)group %(TeamTemporal)group
 *         %(MonsterAcademy)group %(SpectrumLabs)group
 * @Licenses: %(libNIMH-Documentation)path/LICENSES.txt
 * @Creation: 3176-4-52
 *
 *== Revisions
 * + 3176-4-52 Created fire
 * ~ 3176-5-22 Changed a replace function to replace a regex with a list
 * + 3176-5-22 Add replace functions that work on nimh_strings rather than
 * 		nimh_regex. One replaces with a string--the other with a list
 * ~ 3176-5-22 Updated nimh-doc's metadata system usage
 * + 3176-5-22 Added nimh_token alias to nimh_string to add syntactically 
 * 		clarity
 * + 3176-5-22 Added simplistic locale table for use, when lacking modules
 * ~ 3176-5-22 Changed macro name, to avoid conflicting with nimh_token type 
 * 		alias
 * + 3176-5-22 Added function to test, if we already have an entry for this
 * 		symbol in another locale
 * + 3176-5-22 Messed with the equality checking functions. Use match if 
 * 		you only plan to stay in THIS locale
 * + 3176-5-22 added alias functionality
 *
 *== TODO
 *
 * ! Need to comment more
 *
 * == BUG WATCH
 * ! 3176-5-22 may have created a bug by tacking on the limit argument in 
 * 		the replace code
 *
 */


#ifndef __libNIMH_TIME_H__
#define __libNIMH_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

/* == Object
 * 
 * === nimh_string
 * @Field : language_instance : int : a unique id to use here
 * @Field : locale : char[] : this specific strings locale (initialised)
 * @Field : content : char[] : this string's content
 * @Field : stale : bool : a flag to show if this string is stale (for garbage
 * 			collection purposes)
 *
 * Standard string holder.
 *
 */

typedef struct {
    int language_instance;
    char *locale;
    char *content;
    bool stale;
} nimh_string_dat, nimh_string;

/*
 * === nimh_token
 * @Alias : nimh_string
 *
 * nimh_token is mostly used when it would syntactically look nicer to do 
 * this. Or give a clearer idea of what is going on.
 *
 */

typedef nimh_string nimh_token;

/* === nimh_locale_link
 * @Field : a : nimh_token * : first string to match
 * @Field : b : nimh_token * : second string to match
 * @Field : NEXT : void * : linked list var
 * @Field : PREV : void * : linked list var
 *
 * A table specifically for use on checking locale equivilents.
 *
 * Should not be looked at, when SQLite3 or other database solutions are 
 * loaded. (Updated... not checked).
 *
 */
typedef struct {
	nimh_token *a, *b;
	void *NEXT, *PREV;
} nimh_locale_link_dat, nimh_locale_link;

/*
 * === nimh_token_alias
 * @Alias : nimh_locale_link
 *
 * Why not do something silly--like make a variable that reads properly for 
 * just doing token aliases.
 */

typedef nimh_locale_link nimh_token_alias


/* == Methods
 *
 */

/* == nimh_string
 * @Param : nimh_book * : my book
 * @Param : char[] : my locale
 * @Param : char[] : my string
 * @Return : nimh_string
 *
 * Create a string--or match a string from our current table 
 */
nimh_string* nimh_string(nimh_book *, char *, char *);

/* == create_nimh_token
 *
 * This is pretty much the same as nimh_string. For all purposes presented.
 * It is just for syntactical brilliance
 *
 */
#define create_nimh_token(x, y, z) nimh_string(x, y, z)

/* == has_token
 * @Param : nimh_book * : my book
 * @Param : char[] : locale
 * @Param : char[] : content
 * @Return : nimh_string | nil
 *
 * check if we have the token already. A short cut we can call from nimh_string
 *
 */
nimh_string* has_token(nimh_book *, char *, char *);

/*
 * == nimh_match
 * @Param : nimh_book * : my book
 * @Param : nimh_string * : the string to match
 * @Return : bool | int
 *
 * A simple match function. Depending on the context, returns a boolean for 
 * match, or the match count.
 *
 */
bool nimh_match(nimh_book *, nimh_string *, nimh_regex *);
int nimh_match(nimh_book *, nimh_string *, nimh_regex *);

/*
 * == nimh_replace
 * @Param : nimh_book * : my_book
 * @Param : nimh_string * : string to match
 * @Param : nimh_string * | nimh_regex * : match against
 * @Param : nimh_string * | nimh_list * : replace matches with.
 * @Param : int : limit matches
 * @Return : int : match count
 *
 * A standard search and replace string function
 */
int nimh_replace(nimh_book *, nimh_string *, nimh_string *, nimh_string *, int limit=0);
int nimh_replace(nimh_book *, nimh_string *, nimh_string *, nimh_list *, int limit=0);
int nimh_replace(nimh_book *, nimh_string *, nimh_regex *, nimh_string *, int limit=0);
int nimh_replace(nimh_book *, nimh_string *, nimh_regex *, nimh_list *, int limit=0);

/*
 * == nimh_equal
 * @Param : nimh_book * : my book
 * @Param : nimh_string * : token to match
 * @Param : nimh_string * | nimh_regex * : check for equality
 * @Return : bool
 *
 * Different from nimh_match, as nimh_string vs. nimh_string here, requires 
 * full matching (or locale table equivilence).
 *
 * The nimh_string vs. nimh_regex also matches against all locale equivilents.
 * Use sparingly.
 *
 * No, really--this should not appear anywhere locales are not required to be
 * talked to.
 *
 * I will hunt you down and gut you with a knife should you decide that this 
 * is okay to throw about your code willy nilly. We do not need that crap
 * here.
 *
 * I am looking at you, SRB2, PHP devrs, Java devrs and Visual Basic 6 devrs 
 * (VB.Net devrs however get off on an insanity plea... ). Ruby users do not 
 * have any excuse as technically it IS in the documentation (Perl, Python, 
 * C, C++, C#, Lisp, Erlang, Haskell, Pascal, Delphi, ASM, Forth, etc., users
 * likely know better.)
 *
 * Intercal, unlambda, Malbolge, brainfvck, whitespace, etc. users are more 
 * than welcome to use this part, however. I mean--adding locale support to 
 * CINtercal almost demands doing this crap.
 *
 * I may not know where you live--but if you take cell phone pictures with GPS
 * coordinates, play four square, activate GPS local in a web browser or have
 * contact info online--it should not be hard to show up at your house with a 
 * shovel, thumb tacks, bleach and several pounds worth of shoe polish.
 *
 * DO NOT USE THIS CODE UNLESS YOUR MATCHING NEEDS TO GO INTO LOCALE AREAS!
 *
 */
bool nimh_equal(nimh_book *, nimh_string *, nimh_string *);
bool nimh_equal(nimh_book *, nimh_string *, nimh_regex *);

/*
 * === change_locale
 * @Param: nimh_book *: my book
 * @Param: char[]: new locale
 * @Return: side effect to flag new locale
 * @Return: side effect symbol table reworking
 *
 * Change what language we are talking. Note that a locale table will need to
 * be set up...
 *
 * Will also change the symbol table's pointer system. Since most of these 
 * strings are for libNIMH internal usage (to make it easier on the 
 * developers)--it may be best to ensure your module is in your locale.
 */
void change_locale(nimh_book *, char *);

/*
 * === has_locale_for
 * @Param: nimh_book *: my book
 * @Param: nimh_string *: my token
 * @Param: char[] : locale to check for
 * @Return: bool
 *
 * Check to see if we have not already got an entry for the locale you are 
 * adding
 *
 */
bool has_locale_for(nimh_book *, nimh_string *, char *);

/*
 * === locale_table_link
 * @Param: nimh_book *: my book
 * @Param: nimh_string *: token a
 * @Param: nimh_string *: token b
 * @Return: Side Effect of linking table
 * @Return: error exception if token a already has a locale for token b
 *
 * link two tokens based on locales. Since we do have a handidandy check
 * function above this point, if we throw an exception, it takes an extra
 * resource because you screwed up somewhere.
 *
 * Not adding a "locale_table_link_better" as that would only cause massive
 * headaches in the source code design.
 *
 * Perhaps look into alias instead, mayhaps?
 *
 */
void locale_table_link(nimh_book *, nimh_string *, nimh_string *);

/*
 * === alias_token
 * @Param: nimh_book * : my book
 * @Param: nimh_string * : current symbol
 * @Param: nimh_string * : New symbol to lead to that
 * @Return: Side effect--new entry in alias table that links the
 * 		data to both tokens.
 */

void alias_token(nimh_book *, nimh_string *, nimh_string *);

#ifdef __cplusplus
};
#endif
#endif /* end __libNIMH_TIME_H__ */
