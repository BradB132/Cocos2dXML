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

#include "APSResourceArray.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

APSResourceArray::APSResourceArray(APSResource *container, unsigned int capacity) :
m_container(container),
m_isPreloaded(false)
{
    this->reserve(capacity);
}

APSResource *APSResourceArray::getResourceAtIndex(unsigned int index) {
    pair<APSIndex, APSResource *> p = (*this)[index];
    if (!p.second) {
        p.second = this->getResource(p.first);
        (*this)[index] = p;
    }
    return p.second;
}

unsigned int APSResourceArray::getIndexOfApsIndex(APSIndex index) const {
    unsigned int idx = 0;
    APS_FOREACH_CONST(APSResourceArray, *this, iter) {
        if ((*iter).first==index) {
            return idx;
        }
        idx++;
    }
    
    return APS_NIL_INDEX;
}

APSResource *APSResourceArray::getResource(APSIndex index) const {
    if (this->m_container) {
        return this->m_container->getResource(index);
    }
    return NULL;
}

void APSResourceArray::pushBack(APSIndex apsIndex) {
    this->push_back(pair<APSIndex, APSResource *>(apsIndex, NULL));
}

void APSResourceArray::pushBack(APSResource *resource) {
    this->push_back(pair<APSIndex, APSResource *>(resource->getIndex(), resource));
}

void APSResourceArray::insertResource(int index, APSIndex apsIndex) {
    this->insert(this->begin()+ index, pair<APSIndex, APSResource *>(apsIndex, NULL));
}

void APSResourceArray::insertResource(int index, APSResource *resource) {
    this->insert(this->begin()+ index, pair<APSIndex, APSResource *>(resource->getIndex(), resource));
}

void APSResourceArray::preloadAll() {
    if(!m_isPreloaded) {
        int size = this->size();
        
        for (unsigned int i=0; i < size; i++) {
            this->getResourceAtIndex(i);
        }
        
        m_isPreloaded = true;
    }
}

APS_END_NAMESPACE

