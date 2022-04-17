// GuesserGame.cpp : Defines the entry point for the application.
//

#include "GuesserGame.h"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

int exitGame() {
    

    return 0
}

int main()
{
    int value = 50;
    auto action = [&] { value++; };

    auto logo = vbox({
        text("░██████╗░██╗░░░██╗███████╗░██████╗░██████╗███████╗██████╗░░██████╗░░█████╗░███╗░░░███╗███████╗"),
        text("██╔════╝░██║░░░██║██╔════╝██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝░██╔══██╗████╗░████║██╔════╝"),
        text("██║░░██╗░██║░░░██║█████╗░░╚█████╗░╚█████╗░█████╗░░██████╔╝██║░░██╗░███████║██╔████╔██║█████╗░░"),
        text("██║░░╚██╗██║░░░██║██╔══╝░░░╚═══██╗░╚═══██╗██╔══╝░░██╔══██╗██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░"),
        text("╚██████╔╝╚██████╔╝███████╗██████╔╝██████╔╝███████╗██║░░██║╚██████╔╝██║░░██║██║░╚═╝░██║███████╗"),
        text("░╚═════╝░░╚═════╝░╚══════╝╚═════╝░╚═════╝░╚══════╝╚═╝░░╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝"),
        });

    auto buttons = Container::Vertical({
        Button("New Game", action, ButtonOption::Animated()),
        Button("Scoreboard", action, ButtonOption::Animated()),
        Button("Credits", action, ButtonOption::Animated()),
        Button("Exit Game", action, ButtonOption::Animated()),
    });

    auto component = Renderer(buttons, [&] {
        return vbox({
                logo,
                separator(),
                buttons->Render(),
            }) |
            border;
        });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component);

    return EXIT_SUCCESS;
}
