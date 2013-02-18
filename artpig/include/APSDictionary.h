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

#ifndef ArtPigIOS_APSDictionary_h
#define ArtPigIOS_APSDictionary_h

#include "APSObject.h"

APS_BEGIN_NAMESPACE(artpig)

typedef std::map<const std::string, APSObject *> APSDictionaryStorage;

class APSDictionary : public APSObject {
    APS_CLASS_NAME(APSDictionary)

public:
    virtual ~APSDictionary();
    
    /** Creates autoreleased APSDictionary object */
    static APSDictionary *dictionary();
    
    void setObjectForKey(APSObject *object, const std::string &key);
    APSObject *getObjectForKey(const std::string &key);
    
    // Adds the entries from another dictionary.
    void addEntriesFromDictionary(const APSDictionary *otherDictionary);
    
    void removeForKey(const std::string &key);
    
    void clear();
    
    APSDictionaryStorage::iterator begin() { return this->m_table.begin(); }
    APSDictionaryStorage::iterator end() { return this->m_table.end(); }
    

protected:
    APSDictionaryStorage m_table;
};

APS_END_NAMESPACE
#endif
