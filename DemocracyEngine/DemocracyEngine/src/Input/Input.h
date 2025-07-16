#include "../Window/Window.h"
using namespace DemoEngine_Window;

namespace DemoEngine_Input
{
    class EXPORT Input
    {
    private:
        Window* window;
        int currentKey = 0;
        int currentAction = 0;

        double lastX = 0.0;
        double lastY = 0.0;

        bool firstMouse = true;
        bool ShowMouse = false;

    public:
        Input(Window* window);
        ~Input();

        void Update();

        bool IsKeyPressed(int key);
        bool IsKeyReleased(int key);
        void GetMouseDelta(float& deltaX, float& deltaY);
    };
}