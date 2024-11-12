#include "Animation.h"
#include <iostream>

namespace DemoEngine_Animations
{
	Animation::Animation()
	{
		currentTime = 0;
		currentFrame = 0;
		length = std::numeric_limits<unsigned int>::max_digits10;
	}

	Animation::~Animation()
	{

	}

	void Animation::Update(DemoTimer* timer)
	{
		currentTime += DemoTimer::GetDeltaTime();

		while (currentTime > length)
		{
			currentTime -= length;
		}

		float frameLength = length / frames.size();
		currentFrame = static_cast<int>(currentTime / frameLength);
	}

	void Animation::AddFrame(float frameX, float frameY, float frameWidth,
		float frameHeight, float textureWidth, float textureHeight, float durationInSecs)
	{
		length = durationInSecs;

		Frame frame;

		frame.uvCoords[0].u = (frameX / textureWidth);
		frame.uvCoords[0].v = (frameY / textureHeight);

		frame.uvCoords[1].u = ((frameX + frameWidth) / textureWidth);
		frame.uvCoords[1].v = (frameY / textureHeight);

		frame.uvCoords[2].u = (frameX / textureWidth);
		frame.uvCoords[2].v = ((frameY + frameHeight) / textureHeight);

		frame.uvCoords[3].u = ((frameX + frameWidth) / textureWidth);
		frame.uvCoords[3].v = ((frameY + frameHeight) / textureHeight);

		frames.push_back(frame);
	}

	void Animation::AddFrame(float xPosition, float yPosition, float frameWidth,
		float frameHeight, float textureWidth, float textureHeight, float durationInSecs,
		int frameCount)
	{
		length = durationInSecs;

		float frameXIndex = 0;

		for (int i = 0; i < frameCount; i++)
		{
			Frame frame;

			frame.uvCoords[0].u = (xPosition + frameXIndex) / textureWidth;
			frame.uvCoords[0].v = yPosition / textureHeight;

			frame.uvCoords[1].u = (xPosition + frameWidth + frameXIndex) / textureWidth;
			frame.uvCoords[1].v = yPosition / textureHeight;

			frame.uvCoords[2].u = (xPosition + frameXIndex) / textureWidth;
			frame.uvCoords[2].v = (yPosition + frameHeight) / textureHeight;

			frame.uvCoords[3].u = (xPosition + frameWidth + frameXIndex) / textureWidth;
			frame.uvCoords[3].v = (yPosition + frameHeight) / textureHeight;

			frames.push_back(frame);
			frameXIndex += frameWidth;
		}
	}

	void Animation::AddFrame(float xPosition, float yPosition, float frameWidth,
		float frameHeight, float textureWidth, float textureHeight, float durationInSecs,
		int frameCount, int marginsBtwnFrames)
	{
		length = durationInSecs;

		float frameXIndex = 0;

		for (int i = 0; i < frameCount; i++)
		{
			Frame frame;

			frame.uvCoords[0].u = (xPosition + frameXIndex) / textureWidth;
			frame.uvCoords[0].v = yPosition / textureHeight;

			frame.uvCoords[1].u = (xPosition + frameWidth + frameXIndex) / textureWidth;
			frame.uvCoords[1].v = yPosition / textureHeight;

			frame.uvCoords[2].u = (xPosition + frameXIndex) / textureWidth;
			frame.uvCoords[2].v = (yPosition + frameHeight) / textureHeight;

			frame.uvCoords[3].u = (xPosition + frameWidth + frameXIndex) / textureWidth;
			frame.uvCoords[3].v = (yPosition + frameHeight) / textureHeight;

			frames.push_back(frame);
			frameXIndex += frameWidth + marginsBtwnFrames;
		}
	}

	int Animation::GetCurrentFrame()
	{
		return currentFrame;
	}

	std::vector<Frame>& Animation::GetFrames()
	{
		return frames;
	}
}