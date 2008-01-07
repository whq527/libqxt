/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtBerkeley module of the Qt eXTension library
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of th Common Public License, version 1.0, as published by
 ** IBM.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL along with this file.
 ** See the LICENSE file and the cpl1.0.txt file included with the source
 ** distribution for more information. If you did not receive a copy of the
 ** license, contact the Qxt Foundation.
 **
 ** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
 **
 ****************************************************************************/

/**************************************************************************
This is private API. it might change at any time without warning.
****************************************************************************/


#ifndef QxtBdb_H_kpasd
#define QxtBdb_H_kpasd

#include <QFlags>
#include <QString>
#include <qxtglobal.h>



///its impossible to forward anyway,
namespace BerkeleyDB
{
    extern "C"
    {
        #include <db.h>
    }

}

class  QxtBdb 
{
public:
    enum OpenFlag
    {
        CreateDatabase  =0x1,
        ReadOnly        =0x2,
        LockFree        =0x4

    };
    Q_DECLARE_FLAGS(OpenFlags, OpenFlag);

    QxtBdb();
    ~QxtBdb();


    bool get(void* key,int keytype,void* value,int valuetype,u_int32_t flags=NULL,BerkeleyDB::DBC * cursor =0) const ;
    bool get(const void* key,int keytype,void* value,int valuetype,u_int32_t flags=NULL,BerkeleyDB::DBC * cursor =0) const ;


    bool open(QString path,OpenFlags f=0);
    OpenFlags openFlags();
    bool flush();
    BerkeleyDB::DB * db;
    bool isOpen;


};

Q_DECLARE_OPERATORS_FOR_FLAGS(QxtBdb::OpenFlags);





#endif
