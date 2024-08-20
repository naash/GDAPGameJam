#ifndef _IDELEGATOR_
#define _IDELEGATOR_

class IDelegator
{
public:
	virtual ~IDelegator(){};
	virtual int getTextureMixId(int value)= 0;

};

#endif