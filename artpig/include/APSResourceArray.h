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

#ifndef ArtPigIOS_APSResourceArray_h
#define ArtPigIOS_APSResourceArray_h

#include "APSResource.h"

APS_BEGIN_NAMESPACE(artpig)

typedef std::vector<std::pair<APSIndex, APSResource *> > APSResourceArrayStorage;

/**
 @brief	APSResourceArray contains an array of pair<APSIndex, APSResource *> 
 types.
 
 When an APSGraphicGroup object is allocated and initialized from an xml file, 
 it has only children's APSIndex values instead of direct pointer references.
 APSResourceArray lazily aquires and stores APSResource object's pointer
 when it is actually needed.
 
*/
class APSResourceArray : public APSResourceArrayStorage {
    APS_SYNTHESIZE(APSResource *, m_container, Container);     // APSResource object that contains this object.

    APS_SYNTHESIZE_READONLY(bool, m_isPreloaded, IsPreloaded)
    
public:
    /** Constructor of APSResourceArray with a given container resource.
     */
    APSResourceArray(APSResource *container=NULL, unsigned int capacity=4);
    
    /** Returns an APSResource object at index in pair<APSIndex, APSResource *> list.
     */
    APSResource *getResourceAtIndex(unsigned int index);
    
    /** Assigns a pair of APSIndex and APSResource at a given index in 
     pair<APSIndex, APSResource *> list. 
     */
    void setResourceAtIndex(unsigned int index, APSIndex apsIndex, APSResource *resource=NULL) {
        (*this)[index] = std::pair<APSIndex, APSResource *>(apsIndex, resource);
    }
    
    /** Returns APSIndex value at a given index in pair<APSIndex, APSResource *> list. 
     */
    APSIndex getApsIndexAtIndex(unsigned int index) const {
        return (*this)[index].first;
    }
    
    unsigned int getIndexOfApsIndex(APSIndex index) const;
    
    /** Assigns a pair of APSIndex at the end of pair<APSIndex, APSResource *> list. 
     */
    void pushBack(APSIndex apsIndex);
    
    void pushBack(APSResource *resource);
    
    void insertResource(int index, APSIndex apsIndex);
    
    void insertResource(int index, APSResource *resource);
    
    void preloadAll();
    
    
protected:
    /** Returns a resource from symbol. If there is no resource with the index, 
     NULL is returned. 
     */
    APSResource *getResource(APSIndex index) const;
};

APS_END_NAMESPACE

#endif
