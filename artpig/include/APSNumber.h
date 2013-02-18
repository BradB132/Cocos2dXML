/****************************************************************************
 Copyright (c) 2012 ArtPig Software LLC
 
 http://www.artpigsoft.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef ArtPigIOS_APSNumber_h
#define ArtPigIOS_APSNumber_h

#include "APSObject.h"

APS_BEGIN_NAMESPACE(artpig)

typedef union {
    int integer;
    bool boolean;
    unsigned int uInteger;
    long lInteger;
    unsigned long ulInteger;
    float real;
    double lReal;
} APSNumberData;

enum {
    kAPSNumberType_boolean,
    kAPSNumberType_integer,
    kAPSNumberType_uInteger,
    kAPSNumberType_lInteger,
    kAPSNumberType_ulInteger,
    kAPSNumberType_real,
    kAPSNumberType_lReal
};

class APSString;

extern const APSNumberData APSZeroNumberData;

class APSNumber : public APSObject {
    APS_CLASS_NAME(APSNumber)

    APS_SYNTHESIZE(int, m_type, Type)
public:
    APSNumber(int type=kAPSNumberType_integer, APSNumberData data=APSZeroNumberData);
    virtual ~APSNumber();
    
    static APSNumber *numberWithBoolean(bool boolean);
    static APSNumber *numberWithInteger(int integer);
    static APSNumber *numberWithUnsignedInteger(unsigned int uInteger);
    static APSNumber *numberWithLong(long lInteger);
    static APSNumber *numberWithUnsignedLong(unsigned long ulInteger);
    static APSNumber *numberWithFloat(float real);
    static APSNumber *numberWithDouble(double lReal);
    static APSNumber *numberWithBooleanString(const std::string &str);
    
    static APSNumber *numberWithIndex(APSIndex index);
    static APSIndex indexWithNumber(APSNumber *number);
    static unsigned int integerFromIndex(APSIndex index);
    static APSIndex indexFromInteger(unsigned int val);

    bool isKindOfBoolean() const;
    bool isKindOfInteger() const;
    bool isKindOfReal() const;
    
    bool getBoolean() const;
    int getInteger() const;
    unsigned int getUnsignedInteger() const;
    long getLong() const;
    unsigned long getUnsignedLong() const;
    float getFloat() const;
    double getDouble() const;
    
    std::string getString() const;
    

protected:
    APSNumberData m_data;
};

APS_END_NAMESPACE
#endif
