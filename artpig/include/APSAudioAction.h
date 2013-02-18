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

#ifndef ArtPigEditor_APSAudioAction_h
#define ArtPigEditor_APSAudioAction_h

#include "APSAction.h"


APS_BEGIN_NAMESPACE(artpig)

class APSAudioHolder;

/**
 @brief	APSAudioAction manages to play audio in APSAudioHolder.
 */
class APSAudioAction : public APSAction {
    APS_CLASS_NAME(APSAudioAction)

    /** Code reference of APSAudioHolder object.             */
    APS_SYNTHESIZE_STRING_WITH_KEY(m_audioHolderCode, AudioHolderCode)
    
    APS_SYNTHESIZE_WITH_KEY(bool, m_trimmed, Trimmed)
    
    // APS_SYNTHESIZE(double, m_playTimeInTrack, PlayTimeInTrack)
        
public:
    /** Constructor of APSAudioAction. If 'properties' parameter is not NULL, the instance is initialized by the properties.
     */
    APSAudioAction(APSDictionary *properties=NULL);
    
	virtual ~APSAudioAction();
    
    /** Initializes APSAudioAction with given properties.         */
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Preloads audio data before it is used.                      */
    virtual void preloadData();

    /** Returns the type of action.     */
    virtual APSActionType getActionType() const { return kAPSActionTypeAudio; }
    
    /** Plays audio in audioHolder.                                 */
    void play();
    
    /** Returns APSAudioHolder object for audioHolderCode property. */
    APSAudioHolder *getAudioHolder();
    
    /** startFunc() is supposed to be called at the beggining of cocos2d::CCAction's execution.
     @warning startFunc() should be only called by cocos2d::CCAction's execution.
     */
    virtual void stopFunc();
    
    virtual void _interrupt();

protected:
    
    /** Creates and returns an autoreleased cocos2d::CCFiniteTimeAction object that is supposed to run between pre and post actions.
     */
    cocos2d::CCFiniteTimeAction *makeMidCCAction(bool universal=false, float scale=1.0f);

    APSAudioHolder *m_audioHolder;
};

APS_END_NAMESPACE

#endif
