#include <HyperReal/libHyperReal.h>
#include <HyperReal/HyperRealWindow.h>
#include <HyperReal/Monitor.h>

namespace Time
{
    chrono::steady_clock::time_point Now()
    {
        return chrono::high_resolution_clock::now();
    }

    uint64_t Microseconds(chrono::steady_clock::time_point& from, chrono::steady_clock::time_point& now)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(now - from).count();
    }

    chrono::steady_clock::time_point End(chrono::steady_clock::time_point& from, const string& message, int number)
    {
        auto now = chrono::high_resolution_clock::now();
        if (-1 == number)
        {
            printf("[%s] %.4f ms from start\n", message.c_str(), (float)(Microseconds(from, now)) / 1000.0f);
        }
        else
        {
            printf("[%6d - %s] %.4f ms from start\n", number, message.c_str(), (float)(Microseconds(from, now)) / 1000.0f);
        }
        return now;
    }

    string DateTime()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d_%H%M%S"); // Format: YYYYMMDD_HHMMSS
        return oss.str();
    }
}

libHyperReal::libHyperReal() {}
libHyperReal::~libHyperReal() {}

void libHyperReal::Initialize(ui32 width, ui32 height)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    hyperRealWindow = new HyperRealWindow();
    hyperRealWindow->Initialize(width, height);

    /////////glfwSwapInterval(0);  // Disable V-Sync
}

void libHyperReal::Terminate()
{
    if (nullptr != hyperRealWindow)
    {
        delete hyperRealWindow;
    }

    glfwTerminate();
}

void libHyperReal::Run()
{
#ifdef _WINDOWS
    MaximizeConsoleWindowOnMonitor(1);

    MaximizeWindowOnMonitor(glfwGetWin32Window(hyperRealWindow->GetGLFWwindow()), 2);
#endif

    ui32 frameNo = 0;
    auto lastTime = Time::Now();

    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);

    while (!glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        auto now = Time::Now();
        auto timeDelta = (f32)(Time::Microseconds(lastTime, now)) / 1000.0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        glfwSwapBuffers(glfwGetCurrentContext());

        frameNo++;
        lastTime = now;
    }
}
