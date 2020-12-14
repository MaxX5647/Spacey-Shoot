#include "MyAgent.h"
#include "MyObjectAgent.h"

namespace SPACEYSHOOT
{
	void MyObjectAgent::update()
	{
		this->degree += speed;
		if (this->degree >= 360) { this->degree = 0; }
	}
}