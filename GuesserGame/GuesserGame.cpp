// GuesserGame.cpp : Defines the entry point for the application.
//

#include "GuesserGame.h"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

// Game Logo
auto logo = vbox({
        text("░██████╗░██╗░░░██╗███████╗░██████╗░██████╗███████╗██████╗░░██████╗░░█████╗░███╗░░░███╗███████╗"),
        text("██╔════╝░██║░░░██║██╔════╝██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝░██╔══██╗████╗░████║██╔════╝"),
        text("██║░░██╗░██║░░░██║█████╗░░╚█████╗░╚█████╗░█████╗░░██████╔╝██║░░██╗░███████║██╔████╔██║█████╗░░"),
        text("██║░░╚██╗██║░░░██║██╔══╝░░░╚═══██╗░╚═══██╗██╔══╝░░██╔══██╗██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░"),
        text("╚██████╔╝╚██████╔╝███████╗██████╔╝██████╔╝███████╗██║░░██║╚██████╔╝██║░░██║██║░╚═╝░██║███████╗"),
        text("░╚═════╝░░╚═════╝░╚══════╝╚═════╝░╚═════╝░╚══════╝╚═╝░░╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝"),
    });

// Exit Game Code
int exitGame(void) {

    auto screen = ScreenInteractive::FitComponent();
    auto exitAction = [&] { exit(EXIT_SUCCESS); };

    auto buttons = Container::Vertical({
        Button("Exit Game", exitAction, ButtonOption::Animated(Color::Red)),
        });

    auto component = Renderer(buttons, [&] {
        return vbox({
                logo,
                separator(),
                text("Thanks For Playing! Press the button to Exit."),
                separator(),
                buttons->Render(),
            }) |
            border;
        });
    screen.Loop(component);

    exit(EXIT_SUCCESS);
}

// Run Game
int main()
{
    auto screen = ScreenInteractive::FitComponent();
    int value = 50;
    auto action = [&] { value++; };

    auto buttons = Container::Vertical({
        Button("New Game", action, ButtonOption::Animated(Color::Green)),
        Button("Scoreboard", action, ButtonOption::Animated(Color::Blue)),
        Button("Credits", action, ButtonOption::Animated(Color::GrayLight)),
        Button("Exit Game", exitGame, ButtonOption::Animated(Color::Red)),
    });

    auto component = Renderer(buttons, [&] {
        return vbox({
                logo,
                separator(),
                buttons->Render(),
            }) |
            border;
        });
    screen.Loop(component);

    return EXIT_SUCCESS;
}
