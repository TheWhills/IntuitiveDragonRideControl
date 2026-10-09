#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "ModAPI.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <xbyak/xbyak.h>

using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;
using namespace std::literals;

#define DLLEXPORT __declspec(dllexport)

// CommonLibSSE-NG removed the SKSEAPI calling-convention macro in v8.0, but IDRC 8.2 also needs
// the latent-function fix that first shipped in v8.2.0. Define it here so either version builds.
#ifndef SKSEAPI
#	define SKSEAPI __cdecl
#endif

#define RELOCATION_OFFSET(SE, AE) REL::VariantOffset(SE, AE, 0).offset()
#define RELOCATION_OFFSET1799(SE, AE, AE1799) REL::VariantOffset(SE, REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_7_99) == std::strong_ordering::less ? AE : AE1799, 0).offset()

#include "Plugin.h"