#pragma once
#include "shims.h"
#include "shims.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace wasm_shims {
  using Module = ::wasm_shims::Module;
  using ModuleReader = ::wasm_shims::ModuleReader;
  using ModuleWriter = ::wasm_shims::ModuleWriter;
  using InliningOptions = ::wasm_shims::InliningOptions;
  using PassOptions = ::wasm_shims::PassOptions;
  using WasmFeatureSet = ::wasm_shims::WasmFeatureSet;
  using PassRunner = ::wasm_shims::PassRunner;
}
