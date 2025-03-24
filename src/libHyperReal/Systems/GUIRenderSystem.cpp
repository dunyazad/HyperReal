#include <HyperReal/Systems/GUIRenderSystem.h>
#include <HyperReal/libHyperReal.h>

GUIRenderSystem::GUIRenderSystem(libHyperReal* hyperReal, HyperRealWindow* window)
    : ISystem(hyperReal, window)
{
}

GUIRenderSystem::~GUIRenderSystem()
{
}

void GUIRenderSystem::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(libHyperReal::GetInstance().GetHyperRealWindow()->GetGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUIRenderSystem::Terminate()
{
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIRenderSystem::ReloadFont(float newFontSize)
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("../../res/Fonts/NanumGothic/NanumGothic-Regular.ttf", newFontSize);
    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_CreateFontsTexture();
}

void GUIRenderSystem::Update(ui32 frameNo, f32 timeDelta)
{
    if (needFontReload) {
        ReloadFont(fontSize);
        needFontReload = false;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //auto components = Feather.GetInstances<GUIComponentBase>();
    //for (auto& component : components)
    //{
    //    component->Render();
    //}

    ShowUIPanel();
    ShowGraphPanel();
    ShowFPS();
    ShowStatus();
    //ShowTeapotPanel();

    ImGui::Render();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

float GetMemoryUsageMB() {
    return 41.0f;  // Dummy value, replace with real tracking
}

void GUIRenderSystem::ShowFPS()
{
    static const int historySize = 50;  // Number of FPS values to store
    static std::vector<float> fpsHistory(historySize, 60.0f);
    static int historyOffset = 0;
    static float accumulatedFPS = 0.0f;
    static int frameCount = 0;
    static const int updateRate = 10;

    float fps = ImGui::GetIO().Framerate;
    accumulatedFPS += fps;
    frameCount++;

    // Update the graph every few frames
    if (frameCount >= updateRate)
    {
        fpsHistory[historyOffset] = accumulatedFPS / updateRate;
        historyOffset = (historyOffset + 1) % historySize;
        accumulatedFPS = 0.0f;
        frameCount = 0;
    }

    // Position overlay on the top-left
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.7f); // Semi-transparent background

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f); // Rounded corners
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.3f, 0.3f, 0.6f, 0.8f)); // Green background

    if (ImGui::Begin("Performance Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    {
        float memoryUsage = GetMemoryUsageMB();
        ImGui::Text("Mem: %.1fmb", memoryUsage);

        // FPS Display with White Text
        ImGui::Text("FPS: %.1f", fps);

        // Graph (Mini FPS history)
        ImGui::PlotLines("##FPSGraph", fpsHistory.data(), historySize, historyOffset, nullptr, 0.0f, 120.0f, ImVec2(100, 80));

        // Add a settings or alert icon (Dummy Icon)
        ImGui::SameLine();
        ImGui::Text("O");
    }
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}




float amplitude = 1.0f;
float frequency = 1.0f;

void GUIRenderSystem::ShowUIPanel()
{
    ImGui::Begin("Control Panel");

    if (ImGui::SliderFloat("Font Size", &fontSize, 12.0f, 32.0f)) {
        needFontReload = true;
    }

    if (ImGui::Button("Reset")) {
        amplitude = 1.0f;
        frequency = 1.0f;
        fontSize = 20.0f;
        needFontReload = true;
    }
    ImGui::End();
}

void GUIRenderSystem::ShowGraphPanel()
{
    ImGui::Begin("Sine Wave Plot");

    std::vector<float> x_data(100);
    std::vector<float> y_data(100);
    for (size_t i = 0; i < x_data.size(); i++) {
        x_data[i] = i * 0.1f;
        y_data[i] = amplitude * sin(frequency * x_data[i]);
    }

    if (ImPlot::BeginPlot("Sine Wave")) {
        ImPlot::PlotLine("sin(x)", x_data.data(), y_data.data(), (ui32)x_data.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
}


void ToggleButton(const char* str_id, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
    {
        *v = !*v;
        if (true == *v)
        {
            glfwSwapInterval(1);
        }
        else if (false == *v)
        {
            glfwSwapInterval(0);
        }
    }
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height - 5), col_bg, (height - 5) * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius - 2.5f), (radius - 2.5f) - 1.5f, IM_COL32(255, 255, 255, 255));
}

void GUIRenderSystem::ShowStatus()
{
    //float fps = ImGui::GetIO().Framerate;
    //accumulatedFPS += fps;
    //frameCount++;

    //// Update the graph every few frames
    //if (frameCount >= updateRate)
    //{
    //    fpsHistory[historyOffset] = accumulatedFPS / updateRate;
    //    historyOffset = (historyOffset + 1) % historySize;
    //    accumulatedFPS = 0.0f;
    //    frameCount = 0;
    //}

    //// Position overlay on the top-left
    //ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    //ImGui::SetNextWindowBgAlpha(0.7f); // Semi-transparent background

    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f); // Rounded corners
    //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.3f, 0.3f, 0.6f, 0.8f)); // Green background

    //if (ImGui::Begin("Performance Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    //{
    //    //float memoryUsage = GetMemoryUsageMB();
    //    //ImGui::Text("Mem: %.1fmb", memoryUsage);

    //    // FPS Display with White Text
    //    ImGui::Text("V-Sync");
    //    ImGui::SameLine();
    //    ToggleButton("V-Sync", &vSync);
    //    ImGui::Text("FPS: %.1f", fps);

    //    // Graph (Mini FPS history)
    //    ImGui::PlotLines("##FPSGraph", fpsHistory.data(), historySize, historyOffset, nullptr, 0.0f, 120.0f, ImVec2(300, 80));

    //    ImGui::Text("mouse : %4d, %4d", mouseX, mouseY);
    //}
    //ImGui::End();

    //ImGui::PopStyleColor();
    //ImGui::PopStyleVar();
}