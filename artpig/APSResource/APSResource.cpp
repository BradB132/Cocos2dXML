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

#include <iostream>
#include "APSResource.h"
#include "APSSymbol.h"
#include "APSResourceManager.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)


const string &APSResource::getTagKey() {
    static const string key = "tag";
    return key;
}

const string &APSResource::getIndexKey() {
    static const string key = "index";
    return key;
}

const string &APSResource::getParentSymbolKey() {
    static const string key = "parentSymbol";
    return key;
}


APSResource::APSResource(APSDictionary *properties) :m_index(APS_NIL_INDEX),
m_parentSymbol(NULL)
{    
    if (properties) {
        this->initWithProperties(properties);
    }
}

APSResource::~APSResource() {

}


bool APSResource::initWithProperties(APSDictionary *properties) {

    // set index
    APSNumber *indexNum = (APSNumber *)properties->getObjectForKey(this->getIndexKey());
    if (indexNum) {
        this->setIndex(APSNumber::indexWithNumber(indexNum));
    }
    
    // set tag
    APSString *tag = (APSString *)properties->getObjectForKey(this->getTagKey());
    if (tag) {
        this->setTag(tag->c_str());
    }
    
    return true;
}


APSResource *APSResource::getResource(APSIndex index) const {
    APSSymbol *symbol = this->m_parentSymbol;
    if (symbol) {
        return symbol->getResourceAtIndex(index);
    }
    return NULL;
}

APSMedium *APSResource::getMediumForCode(const string &code) {
    APSSymbol *symbol = this->m_parentSymbol;
    if (symbol) {
        return symbol->getResourceManager()->getMediumForCode(code);
    }
    return NULL;
}


APS_END_NAMESPACE

