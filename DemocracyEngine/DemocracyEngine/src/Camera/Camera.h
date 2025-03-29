#include "../Tools/Export.h"
#include "glm/glm.hpp"

#include "../Entities/Entity.h"

using namespace glm;
using namespace DemoEngine_Entities;

namespace DemoEngine_Camera
{

	class EXPORT Camera : Entity
	{
	private:
		float fov;
		float near;
		float far;

		float height;
		float width;

		float up;
		float right;
		float forward;

	public:
		Camera(float fov, float near, float far, float height, float width, float up, float right, float forward, glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);
		Camera(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);
		~Camera();

		void Draw() override;
	};
}