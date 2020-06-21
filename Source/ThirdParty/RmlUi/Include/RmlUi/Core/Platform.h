/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUICOREPLATFORM_H
#define RMLUICOREPLATFORM_H

#if defined __WIN32__ || defined _WIN32
	#define RMLUI_PLATFORM_WIN32
	#define RMLUI_PLATFORM_NAME "win32"
	#if !defined(__MINGW32__)
		#pragma warning(disable:4355)
	#endif
#elif defined __APPLE_CC__
	#define RMLUI_PLATFORM_UNIX
	#define RMLUI_PLATFORM_MACOSX
	#define RMLUI_PLATFORM_NAME "macosx"
#else
	#define RMLUI_PLATFORM_UNIX
	#define RMLUI_PLATFORM_LINUX
	#define RMLUI_PLATFORM_NAME "linux"
#endif

#if !defined NDEBUG && !defined RMLUI_DEBUG
	#define RMLUI_DEBUG
#endif

#if defined __LP64__ || defined _M_X64 || defined _WIN64 || defined __MINGW64__ || defined _LP64
    #define RMLUI_ARCH_64
#else
    #define RMLUI_ARCH_32
#endif


#if defined(RMLUI_PLATFORM_WIN32) && !defined(__MINGW32__)
	// alignment of a member was sensitive to packing
	#pragma warning(disable : 4121)

	// <type> needs to have dll-interface to be used by clients
	#pragma warning(disable : 4251)

	// assignment operator could not be generated
	#pragma warning(disable : 4512)

	// <function> was declared deprecated
	#pragma warning(disable : 4996)

	#if !defined _CRT_SECURE_NO_DEPRECATE
		#define _CRT_SECURE_NO_DEPRECATE
	#endif
#endif

// Wraps unused variables in methods or functions to avoid compiler warnings.  This should
// be wrapped around the name of all parameters that are wrapped with RMLUI_UNUSED_PARAMETER
// to cover warnings generated by non-llvm/gcc style compilers that can't be covered with
// RMLUI_UNUSED_PARAMETER
#if defined __llvm__
//#  define RMLUI_UNUSED(x) UNUSED_ ## x __unused
#  define RMLUI_UNUSED(x)
#elif defined __GNUC__
//#  define RMLUI_UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#  define RMLUI_UNUSED(x)
#else
#  define RMLUI_UNUSED(x) (void)(UNUSED_ ## x)
#endif

// Wraps unused parameter names in method or function declarations.  When used, the first lines
// of the function should contain a matching RMLUI_UNUSED call with the name of the function
// as well to cover compilers with no-op RMLUI_UNUSED_PARAMETER macros.
#if defined __llvm__
#  define RMLUI_UNUSED_PARAMETER(x) UNUSED_ ## x __attribute__((unused))
#elif defined __GNUC__
#  define RMLUI_UNUSED_PARAMETER(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define RMLUI_UNUSED_PARAMETER(x) UNUSED_ ## x
#endif

// RMLUI_UNUSED_ASSERT_PARAMETERS wraps method parameters which are not used in the method other than
// by a RMLUI_ASSERT check.  This safely deals with debug versus release mode configurations
// and will warn if the parameter starts being used when compiled with GCC
#ifdef RMLUI_DEBUG
   // In this case, the parameter is used by a RMLUI_ASSERT test, so we just pass through as is
#  define RMLUI_UNUSED_ASSERT_PARAMETER(x) x
#  define RMLUI_UNUSED_ASSERT(x)
#else
   // If not in DEBUG builds, this parameter is unused, mark it as such
#  if defined __llvm__
#    define RMLUI_UNUSED_ASSERT_PARAMETER(x) UNUSED_ ## x __attribute__((unused))
#    define RMLUI_UNUSED_ASSERT(x)
#  elif defined __GNUC__
#    define RMLUI_UNUSED_ASSERT_PARAMETER(x) UNUSED_ ## x __attribute__((__unused__))
#    define RMLUI_UNUSED_ASSERT(x)
#  else
#    define RMLUI_UNUSED_ASSERT_PARAMETER(x) UNUSED_ ## x
#    define RMLUI_UNUSED_ASSERT(x) (void)(UNUSED_ ## x)
#  endif
#endif

// Wraps functions which are not referenced or exported to avoid compiler warnings
#if defined __llvm__
#  define RMLUI_UNUSED_FUNCTION(x) __attribute__((unused)) UNUSED_ ## x
#elif defined __GNUC__
#  define RMLUI_UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define RMLUI_UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

// Squelchs warnings for unused enums in switch statements, this should only be used for special values
// that are known to NEVER be used.
#define RMLUI_UNUSED_SWITCH_ENUM(x) \
  case x: \
    RMLUI_ERRORMSG("Switch case for unhandled ENUM has been hit!  This shouldn't happen!  ENUM Name: " # x); \
    break;

#endif
