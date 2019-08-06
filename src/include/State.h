#ifndef STATE_H
#define STATE_H
#include "MainMenuOptions.h"


class State
{
public:
    State();
    virtual ~State();
    bool onMainMenuStart;
    bool onOptionSelection;
    bool onLevelSelection;
    bool onCharacterSelection;
    bool onRunningMatch;
    bool transition;
    MainMenuOptions* mainMenuOps;
    std::string levelName;

private:
};

#endif // STATE_H
