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

#ifndef ArtPigIOS_APArray_h
#define ArtPigIOS_APArray_h

#include "APSObject.h"


APS_BEGIN_NAMESPACE(artpig)

typedef std::vector<APSObject *> APSArrayStorage;


/** @brief APSArray manages an array of APSObject objects. 
 */
class APSArray : public APSObject {
    APS_CLASS_NAME(APSArray)

public:
    APSArray();
    APSArray(APSArray *array);
    virtual ~APSArray();
    
    /** Allocates, autorelease, and returns an APSArray object.
     */
    static APSArray *array();
    
    APSObject *getObjectAtIndex(unsigned int index) const;
    
    /** Adds a given APSObject object at the end of array.
     @param object   APSObject object to be added.
     */
    void addObject(APSObject *object);
    
    /** Adds all objects in a given APSArray object.
     @param array   APSArray object to be added.
     */
    void addObjectsFromArray(APSArray *array);
    
    void insertObjectAtIndex(APSObject *object, unsigned int index);
    void removeObjectAtIndex(unsigned int index);
    void clear();
    
    int count() const { return this->m_array.size(); }
    
    APSArrayStorage::iterator begin() { return m_array.begin(); }
    APSArrayStorage::iterator end() { return m_array.end(); }


protected:
    APSArrayStorage m_array;
};

APS_END_NAMESPACE
#endif
