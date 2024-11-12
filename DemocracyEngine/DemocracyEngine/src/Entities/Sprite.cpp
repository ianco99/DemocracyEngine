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

	Sprite::~Sprite()
	{

	}

	void Sprite::Update(DemoTimer* timer)
	{
		if (animation != nullptr)
		{
			animation->Update(timer);
			cout << previousFrame << endl;

			currentFrame = animation->GetCurrentFrame();
			if (currentFrame != previousFrame)
			{
				cout << "Changed frame" << endl;

				Frame newFrame = animation->GetFrames()[currentFrame];

				SetUV(newFrame);

				previousFrame = currentFrame;

			}
		}
		else
		{

			cout << "WARNING: Update being called on a sprite without animation" << endl;
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
		//previousFrame = std::numeric_limits<unsigned int>::max_digits10;
	}

	void Sprite::Draw()
	{
		Renderer::GetRender()->DrawTexture(VAO, indexSize, color, model, textureId);
	}
}
