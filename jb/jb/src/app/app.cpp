#include "app.hpp"

bool app::load()
{
	if (!signature_manager::initialize())
	{
		return false;
	}

	if (!hook_manager::initialize())
	{
		return false;
	}

	return true;
}

bool app::unload()
{
	if (!hook_manager::free())
	{
		return false;
	}

	return true;
}