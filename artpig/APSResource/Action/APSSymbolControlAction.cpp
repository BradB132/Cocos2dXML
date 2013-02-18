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

#include "APSSymbolControlAction.h"
#include "APSSymbol.h"

using namespace cocos2d;
using namespace std;

APS_BEGIN_NAMESPACE(artpig)

void APSSymbolControlAction::resetTarget() {
//    NSLog(@"reset:%s", this->getParentSymbol()->getTag());
    this->getParentSymbol()->initNode();
}

void APSSymbolControlAction::triggerPrologues() {
//    NSLog(@"trigger prologue:%s", this->getParentSymbol()->getTag());
    this->getParentSymbol()->triggerPrologueActionGroups();
}

void APSSymbolControlAction::interruptAllActions() {
//    NSLog(@"interrupt all:%s", this->getParentSymbol()->getTag());
    this->getParentSymbol()->interruptAllActions();
}

#pragma #### Protected ####

// Makes a CCFiniteTimeAction that runs between pre and post actions.
CCFiniteTimeAction * APSSymbolControlAction::makeMidCCAction(bool universal, float scale) {
    
#if COCOS2D_VERSION >= 0x00020000
#define APS_CREATE_METHOD_CCCallFunc(A,B)    CCCallFunc::create(A,B)
#else
#define APS_CREATE_METHOD_CCCallFunc(A,B)    CCCallFunc::actionWithTarget(A,B)
#endif//APS_SKIP
    
    switch (this->getIndex()) {
        case kAPSResetSymbolActionIndex:
            return APS_CREATE_METHOD_CCCallFunc(this, callfunc_selector(APSSymbolControlAction::resetTarget));
        case kAPSTriggerProloguesActionIndex:
            return APS_CREATE_METHOD_CCCallFunc(this, callfunc_selector(APSSymbolControlAction::triggerPrologues));
        case kAPSInterruptAllActionIndex:
            return APS_CREATE_METHOD_CCCallFunc(this, callfunc_selector(APSSymbolControlAction::interruptAllActions));
    }
    return NULL;
        
}

APS_END_NAMESPACE

