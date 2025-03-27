#include "Sprite.h"

namespace DemoEngine_Entities
{
	Sprite::Sprite(const char* textureName, int width, int height, vec4 rgba, vec3 newPosition,
		vec3 newScale, vec3 newRotation, bool filterModeNearest) : Entity2D(newPosition, newRotation, newScale)
	{
		this->width = width;
		this->height = height;

		vertexSize = 36;
		float vertex[] = {
			// positions		    // colors					// texture coords
			0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,	    0.0f, 0.0f,   // bottom left
			-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    0.0f, 1.0f    // top left 
		};

		indexSize = 6;
		int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
		Renderer::GetRender()->BindTexture(textureName, textureId, filterModeNearest);
	}

	Sprite::Sprite(const char* textureName, int textureWidth, int textureHeight, int startX, int startY, int cropWidth, int cropHeight,
		vec4 rgba, vec3 newPosition, vec3 newScale, vec3 newRotation, bool filterModeNearest)
		: Entity2D(newPosition, newRotation, newScale)
	{
		this->width = cropWidth;
		this->height = cropHeight;

		vertexSize = 36;
		float uvX = static_cast<float>(startX) / textureWidth;
		float uvY = static_cast<float>(startY) / textureHeight;
		float uvWidth = static_cast<float>(width) / textureWidth;
		float uvHeight = static_cast<float>(height) / textureHeight;

		float vertex[] = {
			// positions		    // colors					// texture coords
			0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f,     uvX + uvWidth, uvY + uvHeight,   // top right
			0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    uvX + uvWidth, uvY,             // bottom right
			-0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,	    uvX, uvY,                       // bottom left
			-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    uvX, uvY + uvHeight             // top left 
		};

		indexSize = 6;
		int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
		Renderer::GetRender()->BindTexture(textureName, textureId, filterModeNearest);
	}


	Sprite::~Sprite()
	{

	}

	void Sprite::Update(DemoTimer* timer)
	{
		if (animation != nullptr)
		{
			animation->Update(timer);

			currentFrame = animation->GetCurrentFrame();
			if (currentFrame != previousFrame || changedAnim)
			{
				changedAnim = false;
				Frame newFrame = animation->GetFrames()[currentFrame];

				SetUV(newFrame);

				previousFrame = currentFrame;

			}
		}
		else
		{

		}

	}

	void Sprite::SetUV(Frame newFrame)
	{
		float vertex[] = {
			// positions		    // colors					// texture coords
			0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 1.0f,     newFrame.uvCoords[3].u, newFrame.uvCoords[3].v,   // top right
			0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    newFrame.uvCoords[1].u, newFrame.uvCoords[1].v,   // bottom right
			-0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,	    newFrame.uvCoords[0].u, newFrame.uvCoords[0].v,   // bottom left
			-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,	    newFrame.uvCoords[2].u, newFrame.uvCoords[2].v    // top left 
		};

		indexSize = 6;
		int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		Renderer::GetRender()->CreateSprite(VBO, VAO, EBO, vertex, indices, vertexSize, indexSize);
	}

	void Sprite::AddAnimation(Animation* animation)
	{
		this->animation = animation;
		changedAnim = true;
	}

	void Sprite::Draw()
	{
		Renderer::GetRender()->DrawTexture(VAO, indexSize, color, model, textureId);
	}
}
