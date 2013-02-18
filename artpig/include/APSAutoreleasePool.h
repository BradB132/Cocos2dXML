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

#ifndef ArtPigIOS_APSReleasePool_h
#define ArtPigIOS_APSReleasePool_h

#include "APSMacroCPP.h"

#include <string>
#include <map>
#include <vector>


APS_BEGIN_NAMESPACE(artpig)

class APSObject;

/** @brief APSAutoreleasePool manages autoreleased APSObject objects.
 @warning APSAutoreleasePool is not integrated to Operating System or cocos2d framework, so popPool() and pushPool() are should be called manually.
 */
class APSAutoreleasePool : public std::vector<APSObject *> {
public:
    /** Adds an APSObject object at the top pool.
     @param object   APSObject object to be added.
     */
    static void addObject(APSObject *object);
    
    /** Drains the top pool and removes from the pool stack.
     */
    static void popPool();
    
    /** Adds a release pool at the top of the pool stack.
     */
    static void pushPool();
    
    /** Drains all objects in this pool.
     */
    void drain();
};

APS_END_NAMESPACE
#endif
