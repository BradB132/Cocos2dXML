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

#include "APSNumber.h"
#include <sstream>

using namespace std;

APS_BEGIN_NAMESPACE(artpig)

const APSNumberData APSZeroNumberData={0};

#define RETURN_DATA_TYPE(RTYPE)     switch (this->m_type) {\
        case kAPSNumberType_boolean: return (RTYPE)this->m_data.boolean;\
        case kAPSNumberType_integer: return (RTYPE)this->m_data.integer;\
        case kAPSNumberType_uInteger: return (RTYPE)this->m_data.uInteger;\
        case kAPSNumberType_lInteger: return (RTYPE)this->m_data.lInteger;\
        case kAPSNumberType_ulInteger: return (RTYPE)this->m_data.ulInteger;\
        case kAPSNumberType_real: return (RTYPE)this->m_data.real;\
        case kAPSNumberType_lReal: return (RTYPE)this->m_data.lReal;\
        default: return (RTYPE)0;\
    }


APSNumber::APSNumber(int type, APSNumberData data) :
m_type(type),
m_data(data)
{
}

APSNumber::~APSNumber() {
    
}

APSNumber *APSNumber::numberWithBoolean(bool boolean) {
    APSNumberData data;
    data.boolean = boolean;
    return (APSNumber *)(new APSNumber(kAPSNumberType_boolean, data))->autorelease();
}

APSNumber *APSNumber::numberWithInteger(int integer) {
    APSNumberData data;
    data.integer = integer;
    return (APSNumber *)(new APSNumber(kAPSNumberType_integer, data))->autorelease();
}

APSNumber *APSNumber::numberWithUnsignedInteger(unsigned int uInteger) {
    APSNumberData data;
    data.uInteger = uInteger;
    return (APSNumber *)(new APSNumber(kAPSNumberType_uInteger, data))->autorelease();
}

APSNumber *APSNumber::numberWithLong(long lInteger) {
    APSNumberData data;
    data.lInteger = lInteger;
    return (APSNumber *)(new APSNumber(kAPSNumberType_lInteger, data))->autorelease();
}

APSNumber *APSNumber::numberWithUnsignedLong(unsigned long ulInteger) {
    APSNumberData data;
    data.ulInteger = ulInteger;
    return (APSNumber *)(new APSNumber(kAPSNumberType_ulInteger, data))->autorelease();
}

APSNumber *APSNumber::numberWithFloat(float real) {
    APSNumberData data;
    data.real = real;
    return (APSNumber *)(new APSNumber(kAPSNumberType_real, data))->autorelease();
}

APSNumber *APSNumber::numberWithDouble(double lReal) {
    APSNumberData data;
    data.lReal = lReal;
    return (APSNumber *)(new APSNumber(kAPSNumberType_lReal, data))->autorelease();
}


APSNumber *APSNumber::numberWithBooleanString(const string &str) {
    static const string true_string[] = {"true", "TRUE", "yes", "YES" };
    
    bool foundTRUE=false;
    
    for (int i=0; i < 4; i++) {
        if (true_string[i].compare(str)==0) {
            foundTRUE=true;
            break;
        }
    }
    
    return APSNumber::numberWithBoolean(foundTRUE);
}


// APSIndex has 0 as the minimum value, and APS_NIL_INDEX is UINT_MAX value. When an index is stored in property list form, 1 becomes the minimum index value, and 0 represents nil index. 
APSNumber *APSNumber::numberWithIndex(APSIndex index) { 
    return APSNumber::numberWithUnsignedInteger(APS_NIL_INDEX==index? 0 : index+1);
}

APSIndex APSNumber::indexWithNumber(APSNumber *number) {
    APSIndex index =  number->getUnsignedInteger();
    return index==0? APS_NIL_INDEX : index-1;
}

unsigned int APSNumber::integerFromIndex(APSIndex index) {
    return APS_NIL_INDEX==index? 0 : index+1;
}

APSIndex APSNumber::indexFromInteger(unsigned int val) {
    return val==0? APS_NIL_INDEX : val-1;
}

bool APSNumber::isKindOfBoolean() const {
    return this->m_type==kAPSNumberType_boolean;
}

bool APSNumber::isKindOfInteger() const {
    switch (this->m_type) {
        case kAPSNumberType_integer:
        case kAPSNumberType_uInteger:
        case kAPSNumberType_lInteger:
        case kAPSNumberType_ulInteger:
            return true;
    }
    return false;
}

bool APSNumber::isKindOfReal() const {
    switch (this->m_type) {
        case kAPSNumberType_real:
        case kAPSNumberType_lReal:
            return true;
    }
    return false;
    
}

bool APSNumber::getBoolean() const {
    RETURN_DATA_TYPE(int)
}

int APSNumber::getInteger() const {
    RETURN_DATA_TYPE(int)
}

unsigned int APSNumber::getUnsignedInteger() const {
    RETURN_DATA_TYPE(unsigned int)
}

long APSNumber::getLong() const {
    RETURN_DATA_TYPE(long)
}

unsigned long APSNumber::getUnsignedLong() const {
    RETURN_DATA_TYPE(unsigned long)
}

float APSNumber::getFloat() const {
    RETURN_DATA_TYPE(float)
}

double APSNumber::getDouble() const {
    RETURN_DATA_TYPE(double)
}

string APSNumber::getString() const {
    stringstream stream(stringstream::out);

    switch (this->m_type) {
        case kAPSNumberType_boolean:
            if (this->m_data.boolean) {
                stream << "true";
            } else {
                stream << "false";
            }
            break;
        case kAPSNumberType_integer:
            stream << this->m_data.integer;
            break;
        case kAPSNumberType_uInteger:
            stream << this->m_data.uInteger;
            break;
        case kAPSNumberType_lInteger:
            stream << this->m_data.lInteger;
            break;
        case kAPSNumberType_ulInteger:
            stream << this->m_data.ulInteger;
            break;
        case kAPSNumberType_real:
            stream << this->m_data.real;
            break;
        case kAPSNumberType_lReal:
            stream << this->m_data.lReal;
            break;
        default:
            break;
    }
    
    return stream.str();
}

APS_END_NAMESPACE





