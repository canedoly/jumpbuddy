#include "hook_manager.hpp"

#include <vector>

std::vector<Hook *> hooks{};

Hook::Hook(void *initfn)
{
    m_initfn = initfn;

    hooks.push_back(this);
}

bool hook_manager::initialize()
{
    if (MH_Initialize() != MH_OK)
    {
        return false;
    }
    
    for (const auto &hook : hooks)
    {
        reinterpret_cast<void(__cdecl *)()>(hook->m_initfn)();
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        return false;
    }

    return true;
}

bool hook_manager::free()
{
    if (MH_Uninitialize() != MH_OK)
    {
        return false;
    }

    return true;
}