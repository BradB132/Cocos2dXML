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

#ifndef ArtPigEditor_APSAudioHolder_h
#define ArtPigEditor_APSAudioHolder_h

#include "APSMedium.h"

APS_BEGIN_NAMESPACE(artpig)

class APSDevice;
class APSAction;
class APSAction;

class APSAudioHolder : public APSMedium {
    APS_CLASS_NAME(APSAudioHolder)
    
    /** isBackground is true if the audio specified by APSAudioHolder is
     relatively long and used for background music.
     */
    APS_SYNTHESIZE_WITH_KEY(bool, m_isBackground, IsBackground)
    
    /** effectId property is a value returned by playEffect() of SimpleAudioEngine.
     */
    APS_SYNTHESIZE_READONLY(unsigned int, m_effectId, EffectId)

    /** An action that currently running audio of APSAudioHolder.           */
    APS_SYNTHESIZE_READONLY(APSAction *, m_runningAction, RunningAction)
    
public:
    APSAudioHolder(const char *code="", APSResourceManager *manager=NULL);
    APSAudioHolder(APSDictionary *properties);
	virtual ~APSAudioHolder();
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Plays the audio for a given action.                     */
    void playForAction(APSAction *action);
    
    /** Stops the currently playing audio for a given action.                     
     stopForAction() is canceled if the given action is not the same one that 
     has triggered playing audio.
     */
    void stopForAction(APSAction *action);
    
    /** Minimizes memory usage.                                 */
    virtual void clearCachedData();
    
    /** preloads the audio before it is used.                   */
    virtual void preloadData();
 
protected:
    void setEffectId(unsigned int effectId) { this->m_effectId = effectId; }
    void setRunningAction(APSAction *runningAction) { this->m_runningAction = runningAction; }
    
    const std::string *m_filePath;
    const std::string *getFilePath();
    
};

#endif

APS_END_NAMESPACE
