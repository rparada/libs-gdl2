/** 
   EOPrivate.m <title>EOPrivate: various definitions</title>

   Copyright (C) 2005 Free Software Foundation, Inc.

   Date: Jan 2005

   $Revision$
   $Date$

   <abstract></abstract>

   This file is part of the GNUstep Database Library.

   <license>
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
   </license>
**/

#include "config.h"

RCS_ID("$Id$")

#include <Foundation/Foundation.h>

#ifndef GNUSTEP
#include <GNUstepBase/GNUstep.h>
#include <GNUstepBase/GSCategories.h>
#endif

#include <EOControl/EOFault.h>
#include <EOControl/EOMutableKnownKeyDictionary.h>
#include <EOAccess/EODatabaseContext.h>

#include "EOPrivate.h"

// ==== Classes ====
Class GDL2EODatabaseContextClass=Nil;
Class GDL2EOAttributeClass=Nil;

// ==== Selectors =====
SEL GDL2_snapshotForGlobalIDSEL;
SEL GDL2__globalIDForObjectSEL;

// ==== IMPs ====
IMP GDL2EODatabaseContext_snapshotForGlobalIDIMP=NULL;
IMP GDL2EODatabaseContext__globalIDForObjectIMP=NULL;

// ==== Init Method ====
void GDL2_EOAccessPrivateInit()
{
  static BOOL initialized=NO;
  if (!initialized)
    {
      GDL2PrivInit();

      // ==== Selectors =====
      GDL2_snapshotForGlobalIDSEL = @selector(snapshotForGlobalID:);
      GDL2__globalIDForObjectSEL = @selector(_globalIDForObject:);

      // ==== Classes ====
      GDL2EODatabaseContextClass = [EODatabaseContext class];
      GDL2EOAttributeClass = [EOAttribute class];

      GDL2EODatabaseContext_snapshotForGlobalIDIMP=[GDL2EODatabaseContextClass instanceMethodForSelector:GDL2_snapshotForGlobalIDSEL];

      GDL2EODatabaseContext__globalIDForObjectIMP=[GDL2EODatabaseContextClass instanceMethodForSelector:GDL2__globalIDForObjectSEL];

    };
}

// ==== EODatabaseContext ====
NSDictionary *
EODatabaseContext_snapshotForGlobalIDWithImpPtr(EODatabaseContext* dbContext,
						IMP* impPtr,
						EOGlobalID* gid)
{
  if (dbContext)
    {
      IMP imp=NULL;
      if (impPtr)
        imp=*impPtr;
      if (!imp)
        {
          if (GSObjCClass(dbContext)==GDL2EODatabaseContextClass
              && GDL2EODatabaseContext_snapshotForGlobalIDIMP)
            imp=GDL2EODatabaseContext_snapshotForGlobalIDIMP;
          else
            imp=[dbContext methodForSelector:GDL2_snapshotForGlobalIDSEL];
          if (impPtr)
            *impPtr=imp;
        }
      return (*imp)(dbContext,GDL2_snapshotForGlobalIDSEL,gid);
    }
  else
    return nil;
};

EOGlobalID* EODatabaseContext_globalIDForObjectWithImpPtr(EODatabaseContext* dbContext,IMP* impPtr,id object)
{
  if (dbContext)
    {
      IMP imp=NULL;
      if (impPtr)
        imp=*impPtr;
      if (!imp)
        {
          if (GSObjCClass(dbContext)==GDL2EODatabaseContextClass
              && GDL2EODatabaseContext__globalIDForObjectIMP)
            imp=GDL2EODatabaseContext__globalIDForObjectIMP;
          else
            imp=[dbContext methodForSelector:GDL2__globalIDForObjectSEL];
          if (impPtr)
            *impPtr=imp;
        }
      return (*imp)(dbContext,GDL2__globalIDForObjectSEL,object);
    }
  else
    return nil;
};
