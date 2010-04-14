/* -*-objc-*-
   EOCheapArray.h

   Copyright (C) 2000,2002,2003,2004,2005 Free Software Foundation, Inc.

   Author: Manuel Guesdon <mguesdon@orange-concept.com>
   Date: Sep 2000

   This file is part of the GNUstep Database Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef __EOCheapArray_h__
#define __EOCheapArray_h__

#ifdef GNUSTEP
#include <Foundation/NSArray.h>
#include <Foundation/NSZone.h>
#else
#include <Foundation/Foundation.h>
#endif



@interface EOCheapCopyArray : NSArray
{
  unsigned int _count;
  id *_contents_array;
  unsigned int _refcount;
}

- (id)initWithArray: (NSArray *)array;
- (id)initWithObjects: (id *)objects
		count: (NSUInteger)count;
- (void)release;
- (unsigned int)retainCount;
- (id)retain;
- (id)objectAtIndex: (unsigned int)index;
//- (id)copyWithZone: (NSZone *)zone;
- (unsigned int)count;
//- (BOOL)containsObject: (id)obejct;

@end


@interface EOCheapCopyMutableArray : NSMutableArray
{
  unsigned int _count;
  id *_contents_array;
  unsigned int _capacity;
  unsigned int _grow_factor;
  id _immutableCopy;
}

- (id)initWithCapacity: (NSUInteger)capacity;
- (id)initWithObjects: (id *)objects
		count: (NSUInteger)count;
- (id)initWithArray: (NSArray *)array;
- (void)dealloc;
- (NSArray *)shallowCopy;
- (void)_setCopy: (id)param0;
- (void)_mutate;
- (unsigned int)count;
- (id)objectAtIndex: (unsigned int)index;
- (void)addObject: (id)object;
- (void)insertObject: (id)object
	     atIndex: (unsigned int)index;
- (void)removeLastObject;
- (void)removeObjectAtIndex: (unsigned int)index;
- (void)replaceObjectAtIndex: (unsigned int)index
		  withObject: (id)object;
//- (BOOL)containsObject: (id)object;
//- (unsigned int)indexOfObjectIdenticalTo: (id)object;
//- (void)removeAllObjects;
- (void)exchangeObjectAtIndex: (unsigned int)index1
	    withObjectAtIndex: (unsigned int)index2;
@end


#endif //__EOCheapArray_h__
