/** 
   EOAdaptorContext.m <title>EOAdaptorContext Class</title>

   Copyright (C) 2000,2002,2003,2004,2005 Free Software Foundation, Inc.

   Author: Mirko Viviani <mirko.viviani@gmail.com>
   Date: February 2000

   $Revision$
   $Date$

   <abstract></abstract>

   This file is part of the GNUstep Database Library.

   <license>
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
   </license>
**/

#include "config.h"

#ifdef GNUSTEP
#include <Foundation/NSArray.h>
#include <Foundation/NSValue.h>
#include <Foundation/NSNotification.h>
#include <Foundation/NSUserDefaults.h>
#include <Foundation/NSDebug.h>
#else
#include <Foundation/Foundation.h>
#endif

#ifndef GNUSTEP
#include <GNUstepBase/GNUstep.h>
#include <GNUstepBase/NSDebug+GNUstepBase.h>
#include <GNUstepBase/NSObject+GNUstepBase.h>
#endif

#include <EOControl/EODebug.h>
#include <EOControl/EONSAddOns.h>

#include <EOAccess/EOAdaptor.h>
#include <EOAccess/EOAdaptorContext.h>
#include <EOAccess/EOAdaptorChannel.h>

#include "EOAdaptorPriv.h"


NSString *EOAdaptorContextBeginTransactionNotification = @"EOAdaptorContextBeginTransactionNotofication";
NSString *EOAdaptorContextCommitTransactionNotification = @"EOAdaptorContextCommitTransactionNotofication";
NSString *EOAdaptorContextRollbackTransactionNotification = @"EOAdaptorContextRollbackTransactionNotofication";


@implementation EOAdaptorContext

+ (EOAdaptorContext *)adaptorContextWithAdaptor: (EOAdaptor *)adaptor
{
  return [[[self alloc] initWithAdaptor: adaptor] autorelease];
}

- (id) initWithAdaptor: (EOAdaptor *)adaptor
{
  if ((self = [super init]))
    {
      [adaptor _registerAdaptorContext: self];

      ASSIGN(_adaptor, adaptor);
      _channels = [NSMutableArray new];
      _transactionNestingLevel = 0;

      [self setDebugEnabled: [[self class] debugEnabledDefault]];
    }

  return self;
}

- (void)dealloc
{
  [_adaptor _unregisterAdaptorContext: self];

  DESTROY(_adaptor);
  DESTROY(_channels);

  [super dealloc];
}

- (EOAdaptorChannel *)createAdaptorChannel
{
  [self subclassResponsibility: _cmd];
  return nil;
}

- (NSArray *)channels
{
  SEL sel = @selector(nonretainedObjectValue);
  return [_channels resultsOfPerformingSelector: sel];
}

- (BOOL)hasOpenChannels
{
  int i, count = [_channels count];
  
  for (i = 0; i < count; i++)
    if ([[[_channels objectAtIndex: i] nonretainedObjectValue] isOpen])
      return YES;
  
  return NO;
}

- (BOOL)hasBusyChannels
{
  int i, count = [_channels count];

  for (i = 0; i < count; i++)
    if ([[[_channels objectAtIndex: i] nonretainedObjectValue]
	  isFetchInProgress])
      return YES;
  
  return NO;
}

- (void)setDelegate:delegate
{
  _delegate = delegate;

  _delegateRespondsTo.shouldConnect = 
    [delegate respondsToSelector:@selector(adaptorContextShouldConnect:)];
  _delegateRespondsTo.shouldBegin = 
    [delegate respondsToSelector:@selector(adaptorContextShouldBegin:)];
  _delegateRespondsTo.didBegin = 
    [delegate respondsToSelector:@selector(adaptorContextDidBegin:)];
  _delegateRespondsTo.shouldCommit = 
    [delegate respondsToSelector:@selector(adaptorContextShouldCommit:)];
  _delegateRespondsTo.didCommit = 
    [delegate respondsToSelector:@selector(adaptorContextDidCommit:)];
  _delegateRespondsTo.shouldRollback = 
    [delegate respondsToSelector:@selector(adaptorContextShouldRollback:)];
  _delegateRespondsTo.didRollback =
    [delegate respondsToSelector:@selector(adaptorContextDidRollback:)];
}

- (EOAdaptor *)adaptor
{
  return _adaptor;
}

- delegate
{
  return _delegate;
}

- (void)handleDroppedConnection
{
  [self subclassResponsibility: _cmd];
}

@end


@implementation EOAdaptorContext (EOTransactions)

- (void)beginTransaction
{
  [self subclassResponsibility: _cmd];
}

- (void)commitTransaction
{
  [self subclassResponsibility: _cmd];
}

- (void)rollbackTransaction
{
  [self subclassResponsibility: _cmd];
}

- (void)transactionDidBegin
{
  // Increment the transaction scope
  _transactionNestingLevel++;

  [[NSNotificationCenter defaultCenter]
    postNotificationName: EOAdaptorContextBeginTransactionNotification
    object: self];
//the notification call dbcontext _beginTransaction
}

- (void)transactionDidCommit
{

  // Decrement the transaction scope
  _transactionNestingLevel--;//OK

  //OK
  [[NSNotificationCenter defaultCenter]
    postNotificationName: EOAdaptorContextCommitTransactionNotification
    object: self];


}

- (void)transactionDidRollback
{
  // Decrement the transaction scope
  _transactionNestingLevel--;

  [[NSNotificationCenter defaultCenter]
    postNotificationName: EOAdaptorContextRollbackTransactionNotification
    object: self];
}

 - (BOOL)hasOpenTransaction
 {
   if (_transactionNestingLevel > 0)
     return YES;

   return NO;
 }

- (BOOL)canNestTransactions
{
  [self subclassResponsibility: _cmd];
  return NO;
}

- (unsigned)transactionNestingLevel
{
  return _transactionNestingLevel;
}

+ (void)setDebugEnabledDefault: (BOOL)flag
{
  NSString *yn = (flag ? @"YES" : @"NO");

  [[NSUserDefaults standardUserDefaults] setObject: yn
					 forKey: @"EOAdaptorDebugEnabled"];
}

+ (BOOL)debugEnabledDefault
{
  //OK
  return [[NSUserDefaults standardUserDefaults]
	   boolForKey: @"EOAdaptorDebugEnabled"];
}

- (void)setDebugEnabled:(BOOL)debugEnabled
{
  _debug = debugEnabled;
}

- (BOOL)isDebugEnabled
{
  return _debug;
}

@end /* EOAdaptorContext (EOTransactions) */


@implementation EOAdaptorContext (EOAdaptorContextPrivate)

//_registerAdaptorChannel:
- (void)_channelDidInit: channel
{
  [_channels addObject: [NSValue valueWithNonretainedObject: channel]];

  [channel setDebugEnabled: [self isDebugEnabled]]; // not done on reference -- dw
  [channel setDelegate:_delegate];
}

- (void)_channelWillDealloc:channel
{
  int i;
  
  for (i = [_channels count] - 1; i >= 0; i--)
  {
    if ([[_channels objectAtIndex: i] nonretainedObjectValue] == channel)
    {
      [_channels removeObjectAtIndex: i];
      break;
    }
  }
}

@end
