/* 
   EOAttribute.h

   Copyright (C) 2000 Free Software Foundation, Inc.

   Author: Mirko Viviani <mirko.viviani@rccr.cremona.it>
   Date: Feb 2000

   This file is part of the GNUstep Database Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef __EOAttribute_h__
#define __EOAttribute_h__

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSException.h>

#include <gnustep/base/GCObject.h>

#import <EOAccess/EOPropertyListEncoding.h>


@class EOEntity;
@class EOExpressionArray;
@class EOStoredProcedure;


typedef enum {
  EOFactoryMethodArgumentIsNSData = 0,
  EOFactoryMethodArgumentIsNSString,
  EOFactoryMethodArgumentIsBytes
} EOFactoryMethodArgumentType;

typedef enum {
  EOAdaptorNumberType = 0,
  EOAdaptorCharactersType,
  EOAdaptorBytesType,
  EOAdaptorDateType
} EOAdaptorValueType;

typedef enum {
  EOVoid = 0,
  EOInParameter,
  EOOutParameter,
  EOInOutParameter
} EOParameterDirection;


@interface EOAttribute : GCObject <EOPropertyListEncoding>
{
  NSString *_name;
  NSString *_prototypeName;
  NSString *_columnName;
  NSString *_externalType;
  NSString *_valueType;
  NSString *_valueClassName;
  NSString *_readFormat;
  NSString *_writeFormat;
  NSTimeZone *_serverTimeZone;
  unsigned int _width;
  unsigned short _precision;
  short _scale;
  Class _valueClass;
  EOFactoryMethodArgumentType _argumentType;
  NSString *_valueFactoryMethodName;
  NSString *_adaptorValueConversionMethodName;
  SEL _valueFactoryMethod;
  SEL _adaptorValueConversionMethod;
  struct {
    unsigned int allowsNull:1;
    unsigned int isReadOnly:1;
    unsigned int isParentAnEOEntity:1;
    unsigned int protoOverride:17;
    unsigned int unused : 12;
    unsigned int extraRefCount;
  } _flags;
    
  NSDictionary *_sourceToDestinationKeyMap;
  EOParameterDirection _parameterDirection;
  NSDictionary *_userInfo;
  NSDictionary *_internalInfo;
  NSString *_docComment;
  
    /* Garbage collectable objects */
//    EOEntity *_entity;
//    GCMutableArray *_definitionArray;	// These variables are meaningful only
  id _parent;
  EOAttribute *_prototype;
  EOExpressionArray *_definitionArray;
  EOAttribute *_realAttribute;		// if the attribute is flattened //Not in EOF !
}

/** returns an autoreleased attribute owned by onwer and built from propertyList **/
+ (id) attributeWithPropertyList: (NSDictionary *)propertyList
                           owner: (id)owner;

/* Accessing the entity */
- (NSString *)name;

- (EOEntity *)entity;

- (EOStoredProcedure *)storedProcedure;

- (id)parent;

- (NSString *)prototypeName;
- (EOAttribute *)prototype;

- (NSString *)externalType;

- (NSString *)columnName;

- (NSString *)definition;

- (BOOL)isFlattened;

- (BOOL)isDerived;

- (BOOL)isReadOnly;

- (NSString *)valueClassName;

- (NSString *)valueType;

- (unsigned)width;

- (unsigned)precision;

- (int)scale;

- (BOOL)allowsNull;

- (NSString *)writeFormat;
- (NSString *)readFormat;

- (EOParameterDirection)parameterDirection;

- (NSDictionary *)userInfo;

- (NSString *)docComment;

- (BOOL)isKeyDefinedByPrototype: (NSString *)key;

@end


@interface EOAttribute (EOAttributeEditing)

- (NSException *)validateName: (NSString *)name;

- (void)setName: (NSString *)name;

- (void)setPrototypeName: (NSString *)prototypeName;

- (void)setReadOnly: (BOOL)yn;

- (void)setColumnName: (NSString *)columnName;

- (void)setDefinition: (NSString *)definition;

- (void)setExternalType: (NSString *)type;

- (void)setValueType: (NSString *)type;

- (void)setValueClassName: (NSString *)name;

- (void)setWidth: (unsigned)length;

- (void)setPrecision: (unsigned)precision;

- (void)setScale: (int)scale;

- (void)setAllowsNull: (BOOL)allowsNull;

- (void)setWriteFormat: (NSString *)string;

- (void)setReadFormat: (NSString *)string;

- (void)setParameterDirection: (EOParameterDirection)parameterDirection;

- (void)setUserInfo: (NSDictionary *)dictionary;

- (void)setInternalInfo: (NSDictionary *)dictionary;

- (void)setDocComment: (NSString *)docComment;

- (id)_normalizeDefinition: (EOExpressionArray*)definition
                      path: (id)path;

@end


@interface EOAttribute(EOModelBeautifier)
- (void)beautifyName;
@end

@interface EOAttribute (NSCalendarDateSupport)
- (NSTimeZone *)serverTimeZone;
@end

@interface EOAttribute(NSCalendarDateSupportEditing)
- (void)setServerTimeZone: (NSTimeZone *)tz;
@end


@interface EOAttribute (EOAttributeValueCreation)

- (id)newValueForBytes: (const void *)bytes
                length: (int)length;

- (id)newValueForBytes: (const void *)bytes
                length: (int)length
              encoding: (NSStringEncoding)encoding;

- (NSCalendarDate *)newDateForYear: (int)year
                             month: (unsigned)month
                               day: (unsigned)day
                              hour: (unsigned)hour
                            minute: (unsigned)minute
                            second: (unsigned)second
                       millisecond: (unsigned)millisecond
                          timezone: (NSTimeZone *)timezone
                              zone: (NSZone *)zone;

- (NSString *)valueFactoryMethodName;

- (SEL)valueFactoryMethod;

- (id)adaptorValueByConvertingAttributeValue: (id)value;

- (NSString *)adaptorValueConversionMethodName;

- (SEL)adaptorValueConversionMethod;

- (EOAdaptorValueType)adaptorValueType;

- (EOFactoryMethodArgumentType)factoryMethodArgumentType;

@end


@interface EOAttribute(EOAttributeValueCreationEditing)

- (void)setValueFactoryMethodName: (NSString *)factoryMethodName;

- (void)setAdaptorValueConversionMethodName: (NSString *)conversionMethodName;

- (void)setFactoryMethodArgumentType: (EOFactoryMethodArgumentType)argumentType;

@end

@interface EOAttribute(EOAttributeValueMapping)
- (NSException *)validateValue: (id *)valueP;
@end


@interface NSObject (EOCustomClassArchiving)

+ objectWithArchiveData: (NSData *)data;
- (NSData *)archiveData;

@end

#endif /* __EOAttribute_h__ */
