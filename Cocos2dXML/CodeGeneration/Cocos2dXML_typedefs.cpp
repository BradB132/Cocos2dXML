
#include "Cocos2dXML.h"
#include <string.h>
#include <stdio.h>

unsigned char hexToDec(char hexChar)
{
	switch(hexChar)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a':
		case 'A':
			return 10;
		case 'b':
		case 'B':
			return 11;
		case 'c':
		case 'C':
			return 12;
		case 'd':
		case 'D':
			return 13;
		case 'e':
		case 'E':
			return 14;
		case 'f':
		case 'F':
			return 15;
		default:
			return 0;
	}
}

cocos2d::ccColor3B string_to_ccColor3B(const char* colorString)
{
	if(colorString[0] == '#')
		colorString++;

	cocos2d::ccColor3B color;
	color.r = (hexToDec(colorString[0]) << 4) + hexToDec(colorString[1]);
	color.g = (hexToDec(colorString[2]) << 4) + hexToDec(colorString[3]);
	color.b = (hexToDec(colorString[4]) << 4) + hexToDec(colorString[5]);
	return color;
}

Cocos2dXMLColor string_to_Cocos2dXMLColor(const char* colorString)
{
	if(colorString[0] == '#')
		colorString++;
	
	Cocos2dXMLColor color;
	color.rgb = string_to_ccColor3B(colorString);
	color.a = (hexToDec(colorString[6]) << 4) + hexToDec(colorString[7]);
	return color;
}

bool string_to_bool(char* boolString)
{
	return !strcmp(boolString, "true");
}

cocos2d::CCPoint string_to_CCPoint(char* pointString)
{
	cocos2d::CCPoint point;
	point.x = atof(pointString);
	point.y = atof(strchr(pointString, ',')+1);
	return point;
}

bool isKindOfClass(const char* instanceTypeName, const char* desiredTypeName)
{
	if(!strcmp(instanceTypeName, "BaseObject"))
	{
		return (!strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Director"))
	{
		return (!strcmp(desiredTypeName, "Director")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "SceneReference"))
	{
		return (!strcmp(desiredTypeName, "SceneReference")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Transition"))
	{
		return (!strcmp(desiredTypeName, "Transition")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Node"))
	{
		return (!strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Sprite"))
	{
		return (!strcmp(desiredTypeName, "Sprite")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "SpriteBatch"))
	{
		return (!strcmp(desiredTypeName, "SpriteBatch")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "BatchedSprite"))
	{
		return (!strcmp(desiredTypeName, "BatchedSprite")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Scene"))
	{
		return (!strcmp(desiredTypeName, "Scene")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "ClippingNode"))
	{
		return (!strcmp(desiredTypeName, "ClippingNode")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "ParticleSystem"))
	{
		return (!strcmp(desiredTypeName, "ParticleSystem")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Action"))
	{
		return (!strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "FiniteAction"))
	{
		return (!strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "RelativeAction"))
	{
		return (!strcmp(desiredTypeName, "RelativeAction")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Sequence"))
	{
		return (!strcmp(desiredTypeName, "Sequence")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Ease"))
	{
		return (!strcmp(desiredTypeName, "Ease")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Repeat"))
	{
		return (!strcmp(desiredTypeName, "Repeat")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Rotate"))
	{
		return (!strcmp(desiredTypeName, "Rotate")
			|| !strcmp(desiredTypeName, "RelativeAction")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Move"))
	{
		return (!strcmp(desiredTypeName, "Move")
			|| !strcmp(desiredTypeName, "RelativeAction")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Skew"))
	{
		return (!strcmp(desiredTypeName, "Skew")
			|| !strcmp(desiredTypeName, "RelativeAction")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Scale"))
	{
		return (!strcmp(desiredTypeName, "Scale")
			|| !strcmp(desiredTypeName, "RelativeAction")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Tint"))
	{
		return (!strcmp(desiredTypeName, "Tint")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Fade"))
	{
		return (!strcmp(desiredTypeName, "Fade")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Place"))
	{
		return (!strcmp(desiredTypeName, "Place")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Delay"))
	{
		return (!strcmp(desiredTypeName, "Delay")
			|| !strcmp(desiredTypeName, "FiniteAction")
			|| !strcmp(desiredTypeName, "Action")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Animation"))
	{
		return (!strcmp(desiredTypeName, "Animation")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}
	else if(!strcmp(instanceTypeName, "Text"))
	{
		return (!strcmp(desiredTypeName, "Text")
			|| !strcmp(desiredTypeName, "Node")
			|| !strcmp(desiredTypeName, "BaseObject"));
	}

	//coundn't find the type name
	return false;
}

cocos2d::CCObject* newObjectOfType(const char* typeName)
{
	if(!strcmp(typeName, "BaseObject"))
		return new BaseObject();
	if(!strcmp(typeName, "Director"))
		return new Director();
	if(!strcmp(typeName, "SceneReference"))
		return new SceneReference();
	if(!strcmp(typeName, "Transition"))
		return new Transition();
	if(!strcmp(typeName, "Node"))
		return new Node();
	if(!strcmp(typeName, "Sprite"))
		return new Sprite();
	if(!strcmp(typeName, "SpriteBatch"))
		return new SpriteBatch();
	if(!strcmp(typeName, "BatchedSprite"))
		return new BatchedSprite();
	if(!strcmp(typeName, "Scene"))
		return new Scene();
	if(!strcmp(typeName, "ClippingNode"))
		return new ClippingNode();
	if(!strcmp(typeName, "ParticleSystem"))
		return new ParticleSystem();
	if(!strcmp(typeName, "Action"))
		return new Action();
	if(!strcmp(typeName, "FiniteAction"))
		return new FiniteAction();
	if(!strcmp(typeName, "RelativeAction"))
		return new RelativeAction();
	if(!strcmp(typeName, "Sequence"))
		return new Sequence();
	if(!strcmp(typeName, "Ease"))
		return new Ease();
	if(!strcmp(typeName, "Repeat"))
		return new Repeat();
	if(!strcmp(typeName, "Rotate"))
		return new Rotate();
	if(!strcmp(typeName, "Move"))
		return new Move();
	if(!strcmp(typeName, "Skew"))
		return new Skew();
	if(!strcmp(typeName, "Scale"))
		return new Scale();
	if(!strcmp(typeName, "Tint"))
		return new Tint();
	if(!strcmp(typeName, "Fade"))
		return new Fade();
	if(!strcmp(typeName, "Place"))
		return new Place();
	if(!strcmp(typeName, "Delay"))
		return new Delay();
	if(!strcmp(typeName, "Animation"))
		return new Animation();
	if(!strcmp(typeName, "Text"))
		return new Text();

	//coundn't find the type name
	return NULL;
}

