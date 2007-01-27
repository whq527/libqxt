MODULE=QXT_CORE

include (../../config.pri)

VERSION = $$QXVERSION
TEMPLATE = lib
TARGET = QxtCore
DEPENDPATH += .
INCLUDEPATH += . ..

QT = 



QXT_CORE			+= Nullable
QXT_HEADERS_Nullable 	 	= QxtNull.h QxtNullable.h
QXT_STABILITY_Nullable 	 	= +linux-g++

QXT_CORE			+= SingleInstance
QXT_HEADERS_SingleInstance 	 = QxtSingleInstance.h
QXT_STABILITY_SingleInstance 	 = 

QXT_CORE			+= Tuple
QXT_HEADERS_Tuple  		 = QxtTripple.h QxtTuple.h QxtTupleList.h QxtTypeList.h
QXT_STABILITY_Tuple  		 = +linux-g++

QXT_CORE			+= Pimpl
QXT_HEADERS_Pimpl  		 = QxtPimpl.h
QXT_STABILITY_Pimpl  		 = 




include (../parts.pri)
