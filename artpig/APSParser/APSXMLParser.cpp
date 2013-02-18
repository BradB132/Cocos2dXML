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

#include "APSXMLParser.h"

#include <libxml/xmlreader.h>
#include <libxml/tree.h>
#include <iostream>

APS_BEGIN_NAMESPACE(artpig)

using namespace std;

const char *APXML_STRING_KEY = "str";
const char *APXML_BOOLEAN_KEY = "bool";
const char *APXML_INTEGER_KEY = "int";
const char *APXML_REAL_KEY = "real";
const char *APXML_ARRAY_KEY = "array";
const char *APXML_DICTIONARY_KEY = "dict";
const char *APXML_DICTIONARY_ITEM_NAME_KEY = "key";
const char *APXML_VERSION_KEY = "version";
const char *APXML_APLIST_KEY = "APList";

// Returns a new xml node
xmlNodePtr addNode(xmlNodePtr parentNode, APSObject *object);
// Makes an APSObject for the xml node.
APSObject *objectForXmlNode(xmlNodePtr node);



APSXMLParser::APSXMLParser(APSDictionary *dictionary, float version) :
m_dictionary(NULL),
m_version(version)
{
    this->setDictionary(dictionary);
}

APSXMLParser::~APSXMLParser() {
    APS_SAFE_RELEASE(this->m_dictionary)
}

bool APSXMLParser::loadFile(const char *file) {
    xmlDocPtr doc;
    xmlChar *contents;
    
    const unsigned char* pBuffer = NULL;
 	unsigned long bufferSize = 0;
    
#if COCOS2D_VERSION >= 0x00020000
 	pBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(file, "r", &bufferSize);
#else
 	pBuffer = cocos2d::CCFileUtils::getFileData(file, "r", &bufferSize);
#endif//APS_SKIP
    
	doc = xmlParseMemory((const char*)pBuffer, bufferSize);
	if (doc == NULL) {
		return false;
	}
    
	xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr node = root->children;
    contents = xmlNodeGetContent(node);
    if (contents) {
        this->setVersion(atof((const char *)contents));
        
        node = node->next;

        APSAutoreleasePool::pushPool();
        this->setDictionary((APSDictionary *)objectForXmlNode(node));
        APSAutoreleasePool::popPool();
        
    }
    
    xmlFree(contents);
    xmlFreeDoc(doc);
    
    if (pBuffer) {
        delete [] pBuffer;
        pBuffer = NULL;
    }
    
    return true;
}

// Makes an APSObject for the xml node.
APSObject *objectForXmlNode(xmlNodePtr node) {
 /*   
    static map<const string, int> indexes;
    if (indexes.size()==0) {
        indexes[APXML_STRING_KEY]=1;
        indexes[APXML_BOOLEAN_KEY]=2;
        indexes[APXML_INTEGER_KEY]=3;
        indexes[APXML_REAL_KEY]=4;
        indexes[APXML_ARRAY_KEY]=5;
        indexes[APXML_DICTIONARY_KEY]=6;
    }
    */
    APSArray *array;
    APSDictionary *dict;
    
   // const std::string name = (const char *)node->name;
    //std::string content;
    xmlChar *content;
    
    switch(*node->name) {
        case 's': {
            // string
            content = xmlNodeGetContent(node);
            APSString *string = APSString::stringWithString((const char *)content);
            xmlFree(content);
            return string;
        } case 'b': {
            // boolean
            content = xmlNodeGetContent(node);
            APSNumber *number = APSNumber::numberWithBooleanString((const char *)content);
            xmlFree(content);
            return number;
        } case 'i': {
            // integer
            content = xmlNodeGetContent(node);
            APSNumber *number = APSNumber::numberWithLong(atol((const char *)content));
            xmlFree(content);
            return number;
        } case 'r': {
            // real
            content = xmlNodeGetContent(node);
            APSNumber *number = APSNumber::numberWithDouble(atof((const char *)content));
            xmlFree(content);
            return number;
        } case 'a': {
            // array
            array = APSArray::array();
            xmlNodePtr iterNode = node->xmlChildrenNode;
            while (iterNode) {
                APSObject *object = objectForXmlNode(iterNode);
                if (object) {
                    array->addObject(object);
                }
                
                iterNode = iterNode->next;
            }

            return array;
        } case 'd': {
            // dictionary
            dict = APSDictionary::dictionary();
            
            //size = xmlChildElementCount(node);
            xmlNodePtr iterNode = node->xmlChildrenNode;
            //for (int i=1; i < size; i+=2) {
            while (iterNode) {
                content = xmlNodeGetContent(iterNode);
                std::string key = (const char *)content;
                xmlFree(content);
                
                if (key.size() > 0) {
                    iterNode = iterNode->next;
                    APSObject *childObject = objectForXmlNode(iterNode);
                    if (childObject) {
                        dict->setObjectForKey(childObject, key);
                    }
                }
                
                iterNode = iterNode->next;
            }
            return dict;
        }
    }
    
    return NULL;
}

APSDictionary *APSXMLParser::getDictionary() const {
    return m_dictionary;
}

void APSXMLParser::setDictionary(APSDictionary *dictionary) {
    APS_SAFE_RETAIN(dictionary);
    APS_SAFE_RELEASE(m_dictionary)
    this->m_dictionary = dictionary;
}

APS_END_NAMESPACE
