#pragma once

#include "hash/hash.hpp"
#include "hook_manager/hook_manager.hpp"
#include "memory/memory.hpp"
#include "signature_manager/signature_manager.hpp"

#include <intrin.h>
#include <format>

#define MBOX(x) MessageBoxA(0, x, " ", 0)