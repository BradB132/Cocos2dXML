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

#ifndef ArtPigIOS_APSSprite_h
#define ArtPigIOS_APSSprite_h


#include "APSGraphic.h"

APS_BEGIN_NAMESPACE(artpig)

class APSImageHolder;
class APSSpriteSheetHolder;

/** @brief APSSprite
 APSSprite create a cocos2d::CCSprite object. To support multiple screen sizes with 
 different width and height ratio, APSSprite creates cocos2d::CCNode object and attaches
 cocos2d::CCSprite object to it as a child. scaleX and scaleY properties of the cocos2d::CCSprite
 object are adjusted to fit loading image to APSSprite object's width and height
 properties.
 */
class APSSprite : public APSGraphic {
    APS_CLASS_NAME(APSSprite)
    
    APS_SYNTHESIZE_WITH_KEY(bool, m_isAnimatable, IsAnimatable)
    
    APS_SYNTHESIZE_WITH_KEY(bool, m_flipX, FlipX)
    APS_SYNTHESIZE_WITH_KEY(bool, m_flipY, FlipY)
    
    /** A code value referencing to APSImageHolder in APSResourceManager.
     APSImageHolder provides the most appropriate image for the current device.
     */
    APS_SYNTHESIZE_STRING_WITH_KEY(m_imageHolderCode, ImageHolderCode)
public:
    APSSprite(APSDictionary *properties=NULL);
	virtual ~APSSprite();
    
    virtual bool initWithProperties(APSDictionary *properties);
        
    /** Initializes cocos2d::CCNode objects in APSGraphic. initNode() can be called 
     multiple times to reset cocos2d::CCNode objects' states back to original.
     */
    virtual bool initNode();
    
    /** Updates accOpacity, accOpacity value propagates to the all descendant
     graphics. Opacities are multiplied from parent to children thoughout 
     graphics hierarchy. For performance reason, updateAccOpacity() should
     be called as minimum times as you can.
     */
    virtual void updateAccOpacity();
    
    /** Returns an APSImageHolder object in APSResourceManager. imageHolderCode
     must be set to use this method.
     */
    APSImageHolder *getImageHolder();

    APSSpriteSheetHolder *getSpriteSheetHolder();
    
    /** Returns position of this node in parent symbol's coordinations.
     */
    cocos2d::CCPoint getPositionInSymbol();

    /** Assigns properties to a given cocos2d sprite for none ArtPig 
     environment. Properties relative to the symbol's coordinations are 
     assigned to the sprite instead of parent graphic group's coordinations.
     The scale parameter is multiplied to points and sizes to adjust scale of 
     coordinations.
     */
    virtual void assignSpriteProperties(cocos2d::CCSprite *sprite, float scale=1.0f);

    virtual void updateSpriteFrame();
    
protected:
    virtual cocos2d::CCNode *createNode();
    
    cocos2d::CCSprite *m_spriteNode;

    APSImageHolder *m_imageHolder;
};

APS_END_NAMESPACE

#endif
