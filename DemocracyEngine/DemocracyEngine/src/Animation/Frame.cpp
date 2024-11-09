#include "Frame.h"

namespace DemoEngine_Animations
{
	Frame::Frame()
	{

	}

	Frame::~Frame()
	{

	}

	UVCoords* Frame::GetUVCoords()
	{
		return &uvCoords[0];
	}
}