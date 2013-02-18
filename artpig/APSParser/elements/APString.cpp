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

#include "APSString.h"
#include "APSNumber.h"
#include "APSArray.h"
#include "APSResourceArray.h"
#include <sstream>

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


APSString::APSString()
{
}

APSString::APSString(const APSString *str)
{
    this->m_string = str->getString();
}

APSString::APSString(const string &str)
{
    this->m_string = str;
}

APSString::APSString(const APSNumber *number)
{
    this->m_string = number->getString();
}

APSString::APSString(const ccColor4B &color)
{
    unsigned char fields[] = { color.r, color.g, color.b, color.a };
    char buff[4];
    this->m_string="";
    for (int i=0; i < 4; i++) {
        if (fields[i] < 10) {
            sprintf(buff, "00%d",fields[i]);
        } else if(fields[i] < 100) {
            sprintf(buff, "0%d",fields[i]);
        } else {
            sprintf(buff, "%d",fields[i]);
        }
        this->m_string += buff;
    }
}

APSString::APSString(const CCPoint &point) {
    ostringstream oss (ostringstream::out);
    oss << point.x << ',' << point.y;

    this->m_string = oss.str();
}

APSString::APSString(const CCSize &size) {
    ostringstream oss (ostringstream::out);
    oss << size.width << ',' << size.height;
    
    this->m_string = oss.str();
}

APSString::APSString(const CCRect &rect) {
    ostringstream oss (ostringstream::out);
    oss << rect.origin.x << ',' << rect.origin.y << ','
    << rect.size.width << ',' << rect.size.height;
    
    this->m_string = oss.str();
}


APSString::~APSString() {
}

APSString *APSString::stringWithString(const APSString *str) {
    return (APSString *)(new APSString(str))->autorelease();
}

APSString *APSString::stringWithString(const string &str) {
    return (APSString *)(new APSString(str))->autorelease();
}

APSString *APSString::stringWithNumber(const APSNumber *number) {
    return (APSString *)(new APSString(number))->autorelease();
}

APSString *APSString::stringWithColor(const ccColor4B &color) {
    return (APSString *)(new APSString(color))->autorelease();
}

APSString *APSString::stringWithPoint(const CCPoint &point) {
    return (APSString *)(new APSString(point))->autorelease();
}

APSString *APSString::stringWithSize(const CCSize &size) {
    return (APSString *)(new APSString(size))->autorelease();
}

APSString *APSString::stringWithRect(const CCRect &rect) {
    return (APSString *)(new APSString(rect))->autorelease();
}

// Sets APSPathFields of file's location ,filename, and extension.
void APSString::getPathFields(const string &path, APSPathFields *pathFields) {
    if (pathFields) {
        string filename;
        
        // separate path with location and filename
        size_t found = path.rfind("/");
        if (found < path.size()-1) {
            if (found > 0) {
                pathFields->location = path.substr(0, found);
            }
            filename = path.substr(found+1);
        } else {
            // entire string is a filename
            filename = path;
        }
        
        // Separate filename with name and extension
        found = filename.find_last_of('.');
        if (found > 0 && found < filename.size()-1) {
            pathFields->name = filename.substr(0, found);
            pathFields->extension = filename.substr(found+1);
        } else {
            pathFields->name = filename;
        }
    }
}

bool APSString::hasSuffix(const char *str, const char *suffix) {

    int str_len = strlen(str);
    int suff_len = strlen(suffix);
    
    if (str_len < suff_len) {
        return false;
    }
    
    return !strcmp(str+str_len-suff_len, suffix);
}

const char *APSString::getIntsFromString(const char *str, char del, int *values, int maxNValues, int *nValues) {
    char buff[16];
    int index=0;
    const char *ptr = str;
    while (*ptr && index < maxNValues) {
        const char *tv = ptr;
        int size = 0;
        while (*tv && *tv != del) {
            buff[size++]=*tv;;
            tv++;
        }
        buff[size]=0;
        values[index++] = atoi(buff);
        
        if (!*tv) {
            ptr=tv;
            break;
        } else {
            ptr = tv+1;
        }
    }
    *nValues = index;
    return ptr;
}

const char *APSString::getFloatsFromString(const char *str, char del, float *values, int maxNValues, int *nValues) {
    char buff[16];
    int index=0;
    const char *ptr = str;
    while (*ptr && index < maxNValues) {
        const char *tv = ptr;
        int size = 0;
        while (*tv && *tv != del) {
            buff[size++]=*tv;;
            tv++;
        }
        buff[size]=0;
        values[index++] = atof(buff);
        
        if (!*tv) {
            ptr=tv;
            break;
        } else {
            ptr = tv+1;
        }
    }
    *nValues = index;
    return ptr;
}

bool APSString::isEqualToString(APSString *str) const {
    if (strcmp(this->m_string.c_str(),str->c_str())==0) {
        return true;
    }
    return false;
}

const string &APSString::getString() const {
    return this->m_string;
}

const char *APSString::c_str() const {
    return this->m_string.c_str();
}

void APSString::getInts(std::vector<int> *list) const {
    int values[12];
    int size;
    const char *ptr = m_string.c_str();
    
    while (*ptr) {
        ptr = getIntsFromString(ptr, ',', values, 12, &size);

        list->reserve(list->size()+size);

        for(int i=0; i < size; i++) {
            list->push_back(values[i]);
        }
    }
}


void APSString::getFloats(std::vector<float> *list) const {
    float values[12];
    int size;
    const char *ptr = m_string.c_str();
    
    while (*ptr) {
        ptr = getFloatsFromString(ptr, ',', values, 12, &size);
        
        list->reserve(list->size()+size);
        
        for(int i=0; i < size; i++) {
            list->push_back(values[i]);
        }
    }
}

void APSString::getIndexes(std::vector<APSIndex> *list) const {
    this->getInts((vector<int> *)list);
}

void APSString::getResourceArray(APSResourceArray *list) const {
    int values[12];
    int size;
    const char *ptr = m_string.c_str();
    
    while (*ptr) {
        ptr = getIntsFromString(ptr, ',', values, 12, &size);
        
        list->reserve(list->size()+size);
        
        for(int i=0; i < size; i++) {
            list->pushBack(APSNumber::indexFromInteger(values[i]));
        }
    }
}

ccColor4B APSString::getColorValue() const {
    const char *str = m_string.c_str();
    int strLength = strlen(str);
    int fields[] = { 0, 0, 0, 255 };
    char buff[] = { 0, 0, 0, 0 };
    int fieldLength = sizeof(char)*3;
    
    for (int i=0; i < 4; i++) {
        if (i*3+3 <= strLength) {
            memcpy(buff, str+i*3, fieldLength);
            fields[i] = atoi(buff);
        }
    }
    
    return ccc4(fields[0], fields[1], fields[2], fields[3]);
}

CCPoint APSString::getPointValue() const {
    float val[2];
    int size;
    getFloatsFromString(m_string.c_str(), ',', val, 2, &size);

    if (size < 2) {
        return CCPointZero;
    }
    return CCPointMake(val[0], val[1]);
    
    /*
    CCPoint point = CCPointZero;
    
    size_t div = this->m_string.find(',');
    if (div>0 && div < m_string.size()-1) {
        point.x = atof(m_string.substr(0, div).c_str());
        point.y = atof(m_string.substr(div+1).c_str());
    }
    return point;
     */
}

CCSize APSString::getSizeValue() const {
    CCPoint p = this->getPointValue();
    return CCSizeMake(p.x, p.y);
}

CCRect APSString::getRectValue() const {
    /*
    CCRect rect;
    float val[4];
    int pos = 0;
    int size = this->m_string.size();
    
    for (int i=0; i < 3; i++) {
        size_t div = this->m_string.find(',', pos);
        if (div>0 && div < size-1) {
            val[i] = atof(m_string.substr(pos, div-pos).c_str());
        } else {
            return CCRectZero;
        }
        pos = div+1;
    }
    val[3] = atof(m_string.substr(pos, size).c_str());
*/
    float val[4];
    int size;
    getFloatsFromString(m_string.c_str(), ',', val, 4, &size);
    
    if (size < 4) {
        return CCRectZero;
    } else {
        return CCRect(val[0], val[1], val[2], val[3]);
    }
}

APS_END_NAMESPACE





