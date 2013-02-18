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

#ifndef ArtPigIOSX_APXAnimation_h
#define ArtPigIOSX_APXAnimation_h

#include "cocos2d.h"
#include "CCGeometry.h"
#include "APXAnimationObserver.h"
#include "artpig.h"

APS_BEGIN_NAMESPACE(artpig)

class APXAnimation : public cocos2d::CCObject , public APSActionObserver {
public:
    // Allocates and initilaizes an animation with given 'pid' and 'shouldScaleModelToDevice'. If 'shouldScale' is YES, animation scales to fit from model screen to runtime device screen.
    APXAnimation(const char *projectId, bool shouldScaleModelToDevice=true);
    
    virtual ~APXAnimation();

    // Manually changes screen size of device.
    //static void setScreenSize(cocos2d::CCSize &size);

    // Returns an autoreleased APXAnimation object with given 'pid' and 'shouldScaleModelToDevice'. If 'shouldScaleModelToDevice' is YES, animation scales to fit from model screen to runtime device screen.
    static APXAnimation *animationWithProjectId(const char *projectId, bool shouldScaleModelToDevice=true);
    
    // Adds an observer that implements 'willStartAnimation' and 'didFinishAnimation' methods.
    void addObserver(APXAnimationObserver *observer);
    
    // Removes an observer that has been added.
    void removeObserver(APXAnimationObserver *observer);

    // Returns cocos2d::CCLayer object which is the root of graphics tree.
    cocos2d::CCLayer *getRootNode();
    
    // Resets all cocos2d::CCNode objects in the animation to become original state.
    void resetNodes();
    
    void play();
    
    void stop();
    
    float getDuration();

    const char *getProjectId();
    
    bool getShouldScaleModelToDevice() const;
    void setShouldScaleModelToDevice(bool shouldScale);
    
    // Returns true while the animation is playing.
    bool isPlaying();
    
    void willStartAction(APSAction *action);
    void didFinishAction(APSAction *action);

protected:
    
    void notifyObservers();
    
    void setIsPlaying(bool isPlaying);
    
    bool _shouldScaleModelToDevice;
    bool _isPlaying;
    bool _hasPlayed;
    APSSymbol *_symbol;
    std::set<APXAnimationObserver *> _observers;
};

APS_END_NAMESPACE

#endif
