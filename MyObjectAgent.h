#include "MyAgent.h"

namespace SPACEYSHOOT
{
	class MyObjectAgent : public MyAgent
	{
	public:

		MyObjectAgent(float ispeed) : MyAgent(false, false, 2)
		{
			speed = ispeed;
		}

		virtual void update();

	private:

		float speed;
	};
}