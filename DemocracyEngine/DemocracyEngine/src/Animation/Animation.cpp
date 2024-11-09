#include "Animation.h"

namespace DemoEngine_Animations
{
	Animation::Animation()
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::Update(DemoTimer* timer)
	{
		//currentTime += DemoTimer::GetDeltaTime();
		
		while (currentTime > length)
		{
			currentTime -= length;
		}

		//float frameLength = length / fram
	}

	void Animation::AddFrame(float frameX, float frameY, float frameWidth,
		float frameHeight, float textureWidth, float textureHeight, float durationInSecs)
	{

	}

	void Animation::AddFrame(float frameX, float frameY, float frameWidth,
		float frameHeight, float textureWidth, float textureHeight, float durationInSecs,
		int frameCount)
	{

	}

	int Animation::GetCurrentFrame()
	{
		return currentFrame;
	}

	//vector<Frame> Animation::GetFrames()
	//{
	//	return frames;
	//}
}