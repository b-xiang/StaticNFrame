// -------------------------------------------------------------------------
//    @FileName			:    {Filename}
//    @Author           :    GaoYi
//    @Date             :    2017-09-27
//    @Module           :   {Filename}
//
// -------------------------------------------------------------------------

#pragma once

/*
+----------------------------------------------------------------------+
| PHP Version 5                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2009 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
+----------------------------------------------------------------------+
| Modify: weizili                                                      |
+----------------------------------------------------------------------+
*/

/* $Id: md5.h,v 1.17.2.1.2.4 2008/12/31 11:17:45 sebastian Exp $ */

/* MD5.H - header file for MD5C.C
*/

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
*/

#include "NFPlatform.h"

typedef unsigned int php_uint32;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _NFExport
#define PHPAPI _NFExport
#else
#define PHPAPI 
#endif

	/* MD5 context. */
	typedef struct {
		php_uint32 state[4];				/* state (ABCD) */
		php_uint32 count[2];				/* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];	/* input buffer */
	} PHP_MD5_CTX;

	PHPAPI void make_digest(char *md5str, unsigned char *digest);
	PHPAPI void make_digest_ex(char *md5str, unsigned char *digest, int len);
	PHPAPI void PHP_MD5Init(PHP_MD5_CTX *);
	PHPAPI void PHP_MD5Update(PHP_MD5_CTX *, const unsigned char *, unsigned int);
	PHPAPI void PHP_MD5Final(unsigned char[16], PHP_MD5_CTX *);

#ifdef __cplusplus
};
#endif

