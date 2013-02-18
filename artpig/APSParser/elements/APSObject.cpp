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

#include "APSObject.h"
#include "APSAutoreleasePool.h"

using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSObject::getClassNameKey() {
    static const string key = "className";
    return key;
}

APSObject::APSObject() :
m_retainCount(1)
{
}

APSObject::~APSObject() {
    
}

APSObject *APSObject::retain() {
    m_retainCount++; 
    return this;
}

void APSObject::release() {
    if(--m_retainCount<=0) {
        if (m_retainCount<0) {
            APSLOG("retainCount is less than zero.");
        }
        delete this; 
    }
}

APSObject *APSObject::autorelease() {
    APSAutoreleasePool::addObject(this);
    return this;
}

APS_END_NAMESPACE
