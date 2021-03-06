/* -*-objc-*-
   EOSortOrdering.h

   Copyright (C) 2000,2002,2003,2004,2005 Free Software Foundation, Inc.

   Author: Mirko Viviani <mirko.viviani@gmail.com>
   Date: February 2000

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

#ifndef __EOSortOrdering_h__
#define __EOSortOrdering_h__
/* WO45 OK */

#ifdef GNUSTEP
#include <Foundation/NSObject.h>
#include <Foundation/NSArray.h>
#else
#include <Foundation/Foundation.h>
#endif

#include <EOControl/EONull.h>
#include <EOControl/EOKeyValueArchiver.h>


@interface EOSortOrdering : NSObject <NSCoding, NSCopying, EOKeyValueArchiving>
{
  SEL _selector;
  NSString *_key;
}

+ (EOSortOrdering *)sortOrderingWithKey: (NSString *)key
			       selector: (SEL)selector;

- (id)initWithKey: (NSString *)key selector: (SEL)selector;
- (NSString *)key;
- (SEL)selector;

@end


@interface NSArray (EOKeyBasedSorting)

- (NSArray *)sortedArrayUsingKeyOrderArray: (NSArray *)orderArray;

@end


@interface NSMutableArray (EOKeyBasedSorting)

- (void)sortUsingKeyOrderArray: (NSArray *)orderArray;

@end


@interface NSObject (EOSortOrderingComparison)

- (NSComparisonResult)compareAscending: (id)other;
- (NSComparisonResult)compareDescending: (id)other;
- (NSComparisonResult)compareCaseInsensitiveAscending: (id)other;
- (NSComparisonResult)compareCaseInsensitiveDescending: (id)other;

@end


@interface EONull (EOSortOrderingComparison)

- (NSComparisonResult)compareAscending: (id)other;
- (NSComparisonResult)compareDescending: (id)other;
- (NSComparisonResult)compareCaseInsensitiveAscending: (id)other;
- (NSComparisonResult)compareCaseInsensitiveDescending: (id)other;

@end

#define EOCompareAscending @selector(compareAscending:)
#define EOCompareDescending @selector(compareDescending:)
#define EOCompareCaseInsensitiveAscending @selector(compareCaseInsensitiveAscending:)
#define EOCompareCaseInsensitiveDescending @selector(compareCaseInsensitiveDescending:)


#endif
