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

#ifndef ArtPigIOS_APSString_h
#define ArtPigIOS_APSString_h

#include "APSObject.h"

APS_BEGIN_NAMESPACE(artpig)

class APSNumber;
class APSArray;
class APSString;
class APSResourceArray;

struct APSPathFields {
    std::string location;
    std::string name;
    std::string extension;
};

class APSString : public APSObject {
    APS_CLASS_NAME(APSString)

//    APS_SYNTHESIZE_COPY(const string, m_string, String)
public:
    APSString();
    APSString(const APSString *str);
    APSString(const std::string &str);
    APSString(const APSNumber *number);
    APSString(const cocos2d::ccColor4B &color);
    APSString(const cocos2d::CCPoint &point);
    APSString(const cocos2d::CCSize &size);
    APSString(const cocos2d::CCRect &rect);
    

	virtual ~APSString();

    static APSString *stringWithString(const APSString *str);
    static APSString *stringWithString(const std::string &str);
    static APSString *stringWithNumber(const APSNumber *number);
    static APSString *stringWithColor(const cocos2d::ccColor4B &color);
    static APSString *stringWithPoint(const cocos2d::CCPoint &point);
    static APSString *stringWithSize(const cocos2d::CCSize &size);
    static APSString *stringWithRect(const cocos2d::CCRect &rect);    
    
    // Sets APSPathFields of file's location ,filename, and extension.
    static void getPathFields(const std::string &path, APSPathFields *pathFields);
    
    static bool hasSuffix(const char *str, const char *suffix);

    static const char *getIntsFromString(const char *str, char del, int *values, int maxNValues, int *nValues);
    static const char *getFloatsFromString(const char *str, char del, float *values, int maxNValues, int *nValues);
    
    bool isEqualToString(APSString *str) const;
    
    void getInts(std::vector<int> *list) const;
    
    void getFloats(std::vector<float> *list) const;
    
    void getIndexes(std::vector<APSIndex> *list) const;
    
    void getResourceArray(APSResourceArray *list) const;
    
    cocos2d::ccColor4B getColorValue() const;
    
    cocos2d::CCPoint getPointValue() const;
    cocos2d::CCSize getSizeValue() const;
    cocos2d::CCRect getRectValue() const;
    
    const std::string &getString() const;
    
    const char *c_str() const;
    
protected:
    std::string m_string;
    
};

APS_END_NAMESPACE

#endif
