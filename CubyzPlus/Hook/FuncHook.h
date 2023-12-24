#pragma once

class FuncHook {
public:
	virtual bool Initialize() = 0;
};

// include hooks here
#include "Hooks/OpenGLHook.h"
#include "Hooks/ExecBindHook.h"
#include "Hooks/DrawHubIconsHook.h"

void InitHooks() {
	// initialize hooks here
    static FuncHook* hooks[] = {
        // include hooks here
        &OpenGLHook::Get(),
        &DrawHubIconsHook::Get(),
        &ExecBindHook::Get()
    };

    for (std::size_t i = 0; i < std::size(hooks); ++i)
    {
        if (not hooks[i]->Initialize())
        {
            std::cout << "Hook failed to init (id:" << i << ")" << std::endl;
            //error handling
        }
    }
}