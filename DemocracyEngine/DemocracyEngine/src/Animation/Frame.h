#include "../Tools/Export.h"

namespace DemoEngine_Animations
{
	struct EXPORT UVCoords
	{
		float u;
		float v;
	};

	class EXPORT Frame
	{
	public:
		Frame();
		~Frame();

		UVCoords uvCoords[4];
	};
}


