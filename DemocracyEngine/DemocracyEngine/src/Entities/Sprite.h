#pragma once
#include "Shape.h"
#include "../Animation/Animation.h"
#include "../Render/Renderer.h"

using namespace DemoEngine_Animations;
using namespace DemoEngine_Renderer;

namespace DemoEngine_Entities
{
	class EXPORT Sprite : public Entity2D
	{
	protected:
		Animation* animation;
		int currentFrame;
		int previousFrame;

		int width;
		int height;
		unsigned int textureId;

	public:
		Sprite(const char* textureName, int width, int height, vec4 rgba, vec3 newPosition, vec3 newScale,
			   vec3 newRotation);
		Sprite(const char* textureName, int textureWidth, int textureHeight, int startX, int startY, int cropWidth,
			   int cropHeight,
			   vec4 rgba, vec3 newPosition, vec3 newScale, vec3 newRotation);
		~Sprite();

		void SetUV(Frame frame);

		void AddAnimation(Animation* animation);
		void Update(DemoTimer* timer);

		void Draw() override;
	};
}