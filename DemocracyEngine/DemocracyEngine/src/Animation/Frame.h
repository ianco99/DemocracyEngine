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
	private:
		UVCoords uvCoords[4];

	public:
		Frame();
		~Frame();

		UVCoords* GetUVCoords();
	};
}


