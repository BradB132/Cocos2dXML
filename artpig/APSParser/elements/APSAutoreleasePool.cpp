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

#include "APSAutoreleasePool.h"
#include "APSObject.h"

using namespace std;

APS_BEGIN_NAMESPACE(artpig)

static vector<APSAutoreleasePool *> m_poolStack;

// Adds an APSObject object at the top pool
void APSAutoreleasePool::addObject(APSObject *object) {
    if (m_poolStack.size()==0) {
        pushPool();
    }
    APSAutoreleasePool *pool = (*m_poolStack.rbegin());
    pool->push_back(object);
}

// Drains the top pool and removes from the pool stack.
void APSAutoreleasePool::popPool() {
    APSAutoreleasePool *pool = (*m_poolStack.rbegin());
    pool->drain();
    
    if (m_poolStack.size() > 1) {
        // m_poolStack.erase(m_poolStack.begin()+m_poolStack.size()-1);
        m_poolStack.resize(m_poolStack.size()-1);
        delete pool;
    }
}

// Adds a release pool at the top of the pool stack.
void APSAutoreleasePool::pushPool() {
    m_poolStack.push_back(new APSAutoreleasePool);
}

// Drains all objects in this pool.
void APSAutoreleasePool::drain() {
    APS_FOREACH(APSAutoreleasePool, *this, iter) {
        APS_SAFE_RELEASE((*iter));
    }
    this->clear();
}

APS_END_NAMESPACE
