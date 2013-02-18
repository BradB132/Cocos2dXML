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

#ifndef ArtPigIOS_APSResource_h
#define ArtPigIOS_APSResource_h

#include <vector>
#include <set>
#include <map>
#include <iostream>

#include "cocos2d.h"

#include "APSElements.h"
#include "APSPlatform.h"
#include "APSSharedType.h"

#ifdef TEST_COCOS2D_X
using namespace cocos2d;
#endif

APS_BEGIN_NAMESPACE(artpig)

class APSResource;
class APSMedium;
class APSResourceArray;
class APSSymbol;

class  APSResource
: public cocos2d::CCObject
{
    APS_CLASS_NAME(APSResource)
    
    /** Tag is a unique and identifiable value that is specified in 
     ArtPigEditor. With tag property,
     programmers can access an APSResource object. 
     */
    APS_SYNTHESIZE_STRING_WITH_KEY(m_tag, Tag)
    
    /** An index of this resource in parent symbol's resources list
     */
    APS_SYNTHESIZE_WITH_KEY(APSIndex, m_index, Index)
    
    /** An APSSymbol object containing this resource.           */
    APS_SYNTHESIZE_WITH_KEY(APSSymbol *, m_parentSymbol, ParentSymbol)

public:
    /** Constructor of APSResource. If 'properties' parameter is not NULL, the 
     instance is initialized by the properties.
     */
    APSResource(APSDictionary *properties=NULL);    
	virtual ~APSResource();
    
    /** Minimizes memory usage in this resource.                        */
    virtual void clearCachedData() {};
    
    /** Preloads data before it is used.                                */
    virtual void preloadData() {};
    
    /** Initializes this APSResource object with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    
    /** Finds and returns a resource from parent symbol with a given index.
     If there is no resource with the index, NULL is returned.
     With 0 index value, parent symbol is returned.
     @warning parentSymbol property must be set.
     */
    APSResource *getResource(unsigned int index) const;
    
protected:

    /** Returns an APSMedium object with a given code.
     @warning  To use this method, parentSymbol property must be set and the 
     symbol must be created by
     APSResourceManager.
     */
    APSMedium *getMediumForCode(const std::string &code);
        
    friend class APSResourceArray;
};

APS_END_NAMESPACE

#endif
