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

#ifndef ArtPigIOS_APSMacroCPP_h
#define ArtPigIOS_APSMacroCPP_h


#define APS_BEGIN_NAMESPACE(N) namespace N {
#define APS_END_NAMESPACE }

#define APS_SAFE_DELETE(p)			if(p) { delete p; p = 0; }
#define APS_SAFE_DELETE_ARRAY(p)    if(p) { delete[] p; p = 0; }
#define APS_SAFE_FREE(p)			if(p) { free(p); p = 0; }
#define APS_SAFE_RELEASE(p)			if(p) { (p)->release(); p = 0; }
#define APS_SAFE_RETAIN(p)			if(p) { (p)->retain(); }
#define APS_BREAK_IF(cond)			if(cond) break;


/**
 Example:
 APS_PROPERTY_KEY(Position) 
 
 is the same as
 
 public: static const std::string &getPositionKey();
 */
#define APS_PROPERTY_KEY(__FUNC_NAME__) public: static const std::string &get##__FUNC_NAME__##Key();


/**
 Example:
 APS_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_position, Position)
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: inline cocos2d::CCPoint getPosition(void) const { return m_position; }
 */
#define APS_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }


/**
 Example:
 APS_SYNTHESIZE_READONLY_WITH_KEY(cocos2d::CCPoint, m_position, Position) 
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: inline cocos2d::CCPoint getPosition(void) const { return m_position; }
 public: static const std::string &getPositionKey();
 */
#define APS_SYNTHESIZE_READONLY_WITH_KEY(varType, varName, funName)\
APS_SYNTHESIZE_READONLY(varType, varName, funName)\
APS_PROPERTY_KEY(funName)


/**
 Example:
 APS_SYNTHESIZE(cocos2d::CCPoint, m_position, Position)
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: inline cocos2d::CCPoint getPosition(void) const { return m_position; }
 public: inline void setPosition(cocos2d::CCPoint var){ m_position = var; }
 */
#define APS_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }

/**
 Example:
 APS_SYNTHESIZE_REF(cocos2d::CCPoint, m_position, Position)
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: inline cocos2d::CCPoint &getPosition(void) const { return m_position; }
 public: inline void setPosition(cocos2d::CCPoint &var){ m_position = var; }
 */
#define APS_SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType &get##funName(void) const { return varName; }\
public: inline void set##funName(varType &var){ varName = var; }


/**
 Example:
 APS_SYNTHESIZE_WITH_KEY(cocos2d::CCPoint, m_position, Position) 
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: inline cocos2d::CCPoint getPosition(void) const { return m_position; }
 public: inline void setPosition(cocos2d::CCPoint var){ m_position = var; }
 public: static const std::string &getPositionKey();
 */
#define APS_SYNTHESIZE_WITH_KEY(varType, varName, funName)\
APS_SYNTHESIZE(varType, varName, funName)\
APS_PROPERTY_KEY(funName)


/**
 Example:
 APS_PROPERTY(cocos2d::CCPoint, m_position, Position) 
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: virtual cocos2d::CCPoint getPosition(void) const;
 public: virtual void setPosition(cocos2d::CCPoint var);
 */
#define APS_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;\
public: virtual void set##funName(varType var);


/**
 Example:
 APS_PROPERTY_WITH_KEY(cocos2d::CCPoint, m_position, Position) 
 
 is the same as
 
 protected: cocos2d::CCPoint m_position;
 public: virtual cocos2d::CCPoint getPosition(void) const;
 public: virtual void setPosition(cocos2d::CCPoint var);
 public: static const std::string &getPositionKey();
 */
#define APS_PROPERTY_WITH_KEY(varType, varName, funName)\
APS_PROPERTY(varType, varName, funName)\
APS_PROPERTY_KEY(funName)


/**
 Example:
 APS_SYNTHESIZE_STRING(m_tag, Tag) 
 
 is the same as
 
 protected: std::string m_tag;
 public: const char *getTag() const { return this->m_tag.c_str(); }
 public: void setTag(const char *var) { this->m_tag = var; }
 public: const std::string &getTag_string() const { return this->m_tag; }
 */
#define APS_SYNTHESIZE_STRING(varName, funName)\
protected: std::string varName ;\
public: const char *get##funName() const { return this->varName.c_str(); }\
public: void set##funName(const char *var) { this->varName = var; }\
public: const std::string &get##funName##_string() const { return this->varName; }


/**
 Example:
 APS_SYNTHESIZE_STRING_WITH_KEY(m_tag, Tag) 
 
 is the same as
 
 protected: std::string m_tag;
 public: const char *getTag() const { return this->m_tag.c_str(); }
 public: void setTag(const char *var) { this->m_tag = var; }
 public: const std::string &getTag_string() const { return this->m_tag; }
 public: static const std::string &getTagKey();
 */
#define APS_SYNTHESIZE_STRING_WITH_KEY(varName, funName)\
APS_SYNTHESIZE_STRING(varName, funName)\
APS_PROPERTY_KEY(funName)


/**
 Example:
 APS_FOREACH(vector<APSIndex>, indexes, iter)
 
 is the same as
 
 for (vector<APSIndex>::iterator iter = (indexes).begin(), iter_end = (indexes).end(); iter != iter_end; iter++)
 */
#define APS_FOREACH(varType, varName, iterName) \
for (varType::iterator iterName = (varName).begin(), iter_end = (varName).end(); iterName != iter_end; iterName++)


/**
 Example:
 APS_FOREACH_CONST(vector<APSIndex>, indexes, iter)
 
 is the same as
 
 for (vector<APSIndex>::const_iterator iter = (indexes).begin(), iter_end = (indexes).end(); iter != iter_end; iter++)
 */
#define APS_FOREACH_CONST(varType, varName, iterName) \
for (varType::const_iterator iterName = (varName).begin(), iter_end = (varName).end(); iterName != iter_end; iterName++)


//
// Allocating class by class name.
//


/**
 Example:
 APS_ABSTRACT_CLASS_NAME(APSGraphic, Graphic)
 
 is the same as
 
 public: static const std::string &className() { static const std::string cn = "Graphic"; return cn; }
 public: virtual const std::string &getClassName() const { return APSGraphic::className(); }
 */
#define APS_ABSTRACT_CLASS_NAME_KEY(__className__, __key__) \
public: static const std::string &className() { static const std::string cn = #__key__; return cn; } \
public: virtual const std::string &getClassName() const { return __className__::className(); }

/**
 Example:
 APS_ABSTRACT_CLASS_NAME(APSGraphic)
 
 is the same as
 
 public: static const std::string &className() { static const std::string cn = "APSGraphic"; return cn; }
 public: virtual const std::string &getClassName() const { return APSGraphic::className(); }
 */
#define APS_ABSTRACT_CLASS_NAME(__className__) \
public: static const std::string &className() { static const std::string cn = #__className__; return cn; } \
public: virtual const std::string &getClassName() const { return __className__::className(); }


/**
 Example:
 APS_CLASS_NAME(APSGraphic, Graphic)
 
 is the same as
 
 public: static const std::string &className() { static const std::string cn = "Graphic"; return cn; }
 public: virtual const std::string &getClassName() const { return APSGraphic::className(); }
 public: static APSGraphic *alloc() { return new APSGraphic; }
 */
#define APS_CLASS_NAME_KEY(__className__, __key__) \
APS_ABSTRACT_CLASS_NAME_KEY(__className__, __key__) \
public: static __className__ *alloc() { return new __className__; }



/**
 Example:
 APS_CLASS_NAME(APSGraphic)
 
 is the same as
 
 public: static const std::string &className() { static const std::string cn = "APSGraphic"; return cn; }
 public: virtual const std::string &getClassName() const { return APSGraphic::className(); }
 public: static APSGraphic *alloc() { return new APSGraphic; }
 */
#define APS_CLASS_NAME(__className__) \
APS_ABSTRACT_CLASS_NAME(__className__) \
public: static __className__ *alloc() { return new __className__; }


#endif









