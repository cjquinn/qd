#pragma once

extern int main();

namespace Qd {
    class Application {
    public:
        Application();
        virtual ~Application();

    private:
        void run();
        friend int ::main();
    };
}
