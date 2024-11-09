#include <vector>
#include "../Tools/Export.h"
#include "Frame.h"
#include "../Tools/DemoTimer.h"


namespace DemoEngine_Animations
{
	class EXPORT Animation
	{
	private:
		float currentFrame;
		float currentTime;
		float length;

		
		//vector<Frame> frames;

	public:
		Animation();
		~Animation();

		void Update(DemoTimer* timer);
		void AddFrame(float frameX, float frameY, float frameWidth, 
						float frameHeight, float textureWidth, float textureHeight, float durationInSecs);

		void AddFrame(float frameX, float frameY, float frameWidth,
						float frameHeight, float textureWidth, float textureHeight, float durationInSecs, 
						int frameCount);


		int GetCurrentFrame();
		//vector<Frame>& GetFrames();
	};
}


