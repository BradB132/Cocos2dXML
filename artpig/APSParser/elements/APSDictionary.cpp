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

#include "APSDictionary.h"
#include "APSString.h"


APS_BEGIN_NAMESPACE(artpig)

using namespace std;


APSDictionary::~APSDictionary() {
    this->clear();
}

APSDictionary *APSDictionary::dictionary() {
    APSDictionary *dic = new APSDictionary();
    dic->autorelease();
    return dic;
}

void APSDictionary::setObjectForKey(APSObject *object, const string &key) {
    APSDictionaryStorage::iterator iter = this->m_table.find(key);
    if (iter != this->m_table.end()) {
        if (iter->second != object) {
            APS_SAFE_RETAIN(object)
            APS_SAFE_RELEASE(iter->second)
            iter->second = object;
        }
    } else {
        APS_SAFE_RETAIN(object)
        this->m_table[key] = object;
    }
}

APSObject *APSDictionary::getObjectForKey(const string &key) {
    return this->m_table[key];
}

// Adds to the receiving dictionary the entries from another dictionary.
void APSDictionary::addEntriesFromDictionary(const APSDictionary *otherDictionary) {
    // ! Although otherDictionary is converted to none constant object, this loop only accesses its' properties without any change to otherDictionary.
    APS_FOREACH(APSDictionaryStorage,((APSDictionary)*otherDictionary), iter) {
        this->setObjectForKey((*iter).second, (*iter).first);
    }
}

void APSDictionary::removeForKey(const string &key) {
    APSDictionaryStorage::iterator iter = this->m_table.find(key);
    if (iter != this->m_table.end()) {
        APS_SAFE_RELEASE(iter->second);
        this->m_table.erase(iter);
    }
}

void APSDictionary::clear() {
    APS_FOREACH(APSDictionaryStorage, this->m_table, iter) {
        APS_SAFE_RELEASE((*iter).second);
    }
    this->m_table.clear();
}


APS_END_NAMESPACE











