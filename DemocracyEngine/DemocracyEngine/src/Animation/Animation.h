#include "../Tools/Export.h"
#include "Frame.h"
#include "../Tools/DemoTimer.h"
#include <vector>

namespace DemoEngine_Animations
{
	class EXPORT Animation
	{
	private:
		float currentFrame;
		float currentTime;
		float length;



		std::vector<Frame> frames;

	public:
		Animation();
		~Animation();

		void Update(DemoTimer* timer);
		void AddFrame(float frameX, float frameY, float frameWidth,
			float frameHeight, float textureWidth, float textureHeight, float durationInSecs);

		void AddFrame(float frameX, float frameY, float frameWidth,
			float frameHeight, float textureWidth, float textureHeight, float durationInSecs,
			int frameCount);

		void AddFrame(float xPosition, float yPosition, float frameWidth,
			float frameHeight, float textureWidth, float textureHeight, float durationInSecs,
			int frameCount, int marginsBtwnFrames);


			int GetCurrentFrame();
		std::vector<Frame>& GetFrames();
	};
}


