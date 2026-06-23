#include <GlowEngine/core/Application.hpp>

#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>

Application& Application::get_singleton()
{
    static Application instance;
    return instance;
}

void Application::on_compose()
{
    InitWindow(1280, 720, "GlowEngine"); // Initializes the window (tankpillow)
    InitAudioDevice();                   // Might not be needed, but if we want feedback sfx it will be (tankpillow)
    SetTargetFPS(60);                    // Locks framerate at 60 frames per second, might lower (tankpillow)
    SetExitKey(KEY_NULL);                // Disable the use of a key to close the application (tankpillow)

    rlImGuiSetup(true);                  // Sets up ImGui for use with RayLib.

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void Application::on_dispose()
{
    rlImGuiShutdown();  // Cleans up ImGui. 

    CloseAudioDevice(); // Cleans up the audio device (tankpillow)
    CloseWindow();      // Cleans up the window (tankpillow)
}

void Application::on_update(float delta)
{

}

void Application::on_draw()
{
    ImGui::ShowDemoWindow();
}

void Application::run()
{
    Application& self = Application::get_singleton();
    self.on_compose();

    while (!WindowShouldClose()) 
    {   
        float delta = GetFrameTime();
        self.on_update(delta);

        BeginDrawing();
        {
            ClearBackground(BLACK);
            rlImGuiBegin();
            {
                ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode);
                self.on_draw();   
            }
            rlImGuiEnd();
        }
        EndDrawing();
    }

    self.on_dispose();
}
