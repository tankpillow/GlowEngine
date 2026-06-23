#pragma once

class Application
{
    public:
        static Application& get_singleton();
    protected:
        void on_compose();
        void on_dispose();
        void on_update(float delta);
        void on_draw();
    public:
        static void run();
};