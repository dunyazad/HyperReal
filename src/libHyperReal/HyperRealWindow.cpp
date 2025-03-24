#include <HyperReal/HyperRealWindow.h>

HyperRealWindow* HyperRealWindow::s_instance = nullptr;

HyperRealWindow::HyperRealWindow()
{
    s_instance = this;
}

HyperRealWindow::~HyperRealWindow()
{
}

GLFWwindow* HyperRealWindow::Initialize(ui32 width, ui32 height)
{
    this->width = width;
    this->height = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Allows glBegin/glEnd

    window = glfwCreateWindow(width, height, "Feather", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

    return window;
}

void HyperRealWindow::Terminate()
{
    glfwDestroyWindow(window);
}

void HyperRealWindow::FrameBufferSizeCallback(GLFWwindow* window, i32 width, i32 height)
{
    s_instance->width = width;
    s_instance->height = height;

    //////////EventDispatcher::TriggerEvent<FrameBufferResizeEvent>({ width, height });
}
