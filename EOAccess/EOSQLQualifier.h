/* -*-objc-*-
   EOSQLQualifier.h

   Copyright (C) 2000-2002,2003,2004,2005 Free Software Foundation, Inc.

   Author: Mirko Viviani <mirko.viviani@gmail.com>
   Date: February 2000

   Author: Manuel Guesdon <mguesdon@orange-concept.com>
   Date: February 2002

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

#ifndef __EOSQLQualifier_h__
#define __EOSQLQualifier_h__


#ifdef GNUSTEP
#include <Foundation/NSString.h>
#else
#include <Foundation/Foundation.h>
#endif

#include <EOControl/EOQualifier.h>


@class EOSQLExpression;
@class EOExpressionArray;
@class EOEntity;
@class EOModel;


/** Protocol for all qualifiers used used to generate SQL queries **/
@protocol EOQualifierSQLGeneration

- (NSString *)sqlStringForSQLExpression: (EOSQLExpression *)sqlExpression;

/** Returns an equivalent EOQualifier yet having the object references
    replaced by foreign key references. **/
- (EOQualifier *)schemaBasedQualifierWithRootEntity: (EOEntity *)entity;

@end


@interface EOAndQualifier (EOQualifierSQLGeneration) <EOQualifierSQLGeneration>
@end
@interface EOOrQualifier (EOQualifierSQLGeneration) <EOQualifierSQLGeneration>
@end
@interface EOKeyComparisonQualifier (EOQualifierSQLGeneration) <EOQualifierSQLGeneration>
@end
@interface EOKeyValueQualifier (EOQualifierSQLGeneration) <EOQualifierSQLGeneration>
@end
@interface EONotQualifier (EOQualifierSQLGeneration) <EOQualifierSQLGeneration>
@end


@interface EOSQLQualifier : EOQualifier <EOQualifierSQLGeneration> 
{
  EOEntity *_entity;
  EOExpressionArray *_contents;
  struct 
  {
    unsigned int usesDistinct:1;
    unsigned int _RESERVED:31;
  } _flags;
}

+ (EOQualifier *)qualifierWithQualifierFormat: (NSString *)format, ...;

- (id)initWithEntity: (EOEntity *)entity 
     qualifierFormat: (NSString *)qualifierFormat, ...;

@end

@interface NSString (NSStringSQLExpression)
- (NSString *)valueForSQLExpression: (EOSQLExpression *)sqlExpression;
@end

#endif
