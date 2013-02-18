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

#ifndef ArtPigIOS_APSXMLParser_h
#define ArtPigIOS_APSXMLParser_h

#include "APSElements.h"

APS_BEGIN_NAMESPACE(artpig)

extern const char *APXML_STRING_KEY;
extern const char *APXML_BOOLEAN_KEY;
extern const char *APXML_INTEGER_KEY;
extern const char *APXML_REAL_KEY;
extern const char *APXML_ARRAY_KEY;
extern const char *APXML_DICTIONARY_KEY;
extern const char *APXML_DICTIONARY_ITEM_NAME_KEY;


/** @brief APSXMLParser is a utility class that loads XML file in dictionary 
 property. 
 */
class APSXMLParser {
    APS_CLASS_NAME(APSXMLParser)

    /** Loaded objects are stored in dictionary property. */
    APS_PROPERTY(APSDictionary *, m_dictionary, Dictionary)
    
    /** XML file version defined by ArtPig. */
    APS_SYNTHESIZE(float, m_version, Version)
    
public:

    APSXMLParser(APSDictionary *dictionary=NULL, float version=1.0f);
    virtual ~APSXMLParser();
    
    /** Loads XML with a given file and saves in dictionary property.
     */
    virtual bool loadFile(const char *file);  
};

APS_END_NAMESPACE
#endif
