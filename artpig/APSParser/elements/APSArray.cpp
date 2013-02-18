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

#include "APSArray.h"
#include "APSString.h"

using namespace std;

APS_BEGIN_NAMESPACE(artpig)


APSArray::APSArray() {
}

APSArray::APSArray(APSArray *array) {
    this->addObjectsFromArray(array);
}

APSArray::~APSArray() {
    this->clear();
}

APSArray *APSArray::array() {
    APSArray *array = new APSArray();
    array->autorelease();
    return array;
}

APSObject *APSArray::getObjectAtIndex(unsigned int index) const {
    return this->m_array[index];
}

void APSArray::addObject(APSObject *object) {
    if (object) {
        object->retain();
        this->m_array.push_back(object);
    }
}

void APSArray::addObjectsFromArray(APSArray *array) {
    if (array) {
        APS_FOREACH(APSArrayStorage, *array, iter) {
            if (*iter) {
                this->addObject(*iter);
            }
        }
    }
}

void APSArray::insertObjectAtIndex(APSObject *object, unsigned int index) {
    if (object) {
        object->retain();
        this->m_array.insert(this->m_array.begin()+index, object);
    }
}

void APSArray::removeObjectAtIndex(unsigned int index) {
    
    APS_SAFE_RELEASE(this->m_array[index]);
    this->m_array.erase(this->m_array.begin()+index);
}

void APSArray::clear() {
    APS_FOREACH(vector<APSObject *>, this->m_array, iter) {
        APS_SAFE_RELEASE((*iter))
    }
    this->m_array.clear();
}

APS_END_NAMESPACE


