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
    bool onLevelSelction;
    bool onCharacterSelection;
    bool onRunningMatch;
    MainMenuOptions* MM_OPS;

private:
};

#endif // STATE_H
