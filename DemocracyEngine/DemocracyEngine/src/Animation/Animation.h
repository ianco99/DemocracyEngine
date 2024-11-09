#include "../Tools/Export.h"

namespace DemoEngine_Animations
{
	class EXPORT Animation
	{
	private:
		float currentFrame;
		float currentTime;
		float length;

	public:
		Animation();
		~Animation();

		void Update();
		void AddFrame(float frameX, float frameY, float frameWidth, 
						float frameHeight, float textureWidth, float textureHeight, float durationInSecs);

		void addFrame(float frameX, float frameY, float frameWidth,
						float frameHeight, float textureWidth, float textureHeight, float durationInSecs, 
						int frameCount);

		//int currentFrame();
		//vector<Frame>& getFrames();
	};
}


