/*nimh-doc
 * = %(libnimh-includes)path/libnimh.h
 * @Author : %(KatrinaTheLamia)user
 * @Groups : %(NIMHLabs)group, %(SpectrumLabs)group
 * @Projects: %(libNIMH)project
 * @Creation: 3176-5-22
 * @License : %(libnimh-documentation)path/LICENSE.txt
 *
 * Mostly just a standard header, to allow libNIMH to be used in various
 * other applications (provided they link to libNIMH.so or libNIMH.dll)
 *
 * == Revisions
 * + 3176-5-22 File creation
 *
 * == TODO
 * ! Actually make these headers usable
 *
 */

#ifndef __libNIMH_H__
#define __libNIMH_H__

/* Start up our C++ shields  */
#ifdef __cplusplus
extern "C" {
#endif
/* C++ shields up and at full power, captain */

#include <nimh_string.h>
#include <nimh_time.h>
#include <widget.h>
#include <configuration.h>
#include <threading.h>
#include <storage.h>
#include <dynamic_loading.h>
#include <memory_management.h>


/* Drop our C++ shileds  */
#ifdef __cplusplus
};
#endif
#endif /* __libNIMH_H__ is teh over */


