#include "shims.h"
#include "shims.h"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

namespace repr {
struct PtrLen final {
  void *ptr;
  ::std::size_t len;
};
} // namespace repr

namespace detail {
class Fail final {
  ::rust::repr::PtrLen &throw$;
public:
  Fail(::rust::repr::PtrLen &throw$) noexcept : throw$(throw$) {}
  void operator()(char const *) noexcept;
  void operator()(std::string const &) noexcept;
};
} // namespace detail

namespace {
template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};

template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1

namespace behavior {
class missing {};
missing trycatch(...);

template <typename Try, typename Fail>
static typename ::std::enable_if<
    ::std::is_same<decltype(trycatch(::std::declval<Try>(), ::std::declval<Fail>())),
                 missing>::value>::type
trycatch(Try &&func, Fail &&fail) noexcept try {
  func();
} catch (::std::exception const &e) {
  fail(e.what());
}
} // namespace behavior
} // namespace rust

namespace wasm_shims {
  using Module = ::wasm_shims::Module;
  using ModuleReader = ::wasm_shims::ModuleReader;
  using ModuleWriter = ::wasm_shims::ModuleWriter;
  using InliningOptions = ::wasm_shims::InliningOptions;
  using PassOptions = ::wasm_shims::PassOptions;
  using WasmFeatureSet = ::wasm_shims::WasmFeatureSet;
  using PassRunner = ::wasm_shims::PassRunner;
}

namespace Colors {
extern "C" {
void Colors$cxxbridge1$setEnabled(bool enabled) noexcept {
  void (*setEnabled$)(bool) = ::Colors::setEnabled;
  setEnabled$(enabled);
}
} // extern "C"
} // namespace Colors

namespace wasm_shims {
extern "C" {
::wasm_shims::Module *wasm_shims$cxxbridge1$newModule() noexcept {
  ::std::unique_ptr<::wasm_shims::Module> (*newModule$)() = ::wasm_shims::newModule;
  return newModule$().release();
}

bool wasm_shims$cxxbridge1$validateWasm(::wasm_shims::Module &wasm) noexcept {
  bool (*validateWasm$)(::wasm_shims::Module &) = ::wasm_shims::validateWasm;
  return validateWasm$(wasm);
}

::wasm_shims::ModuleReader *wasm_shims$cxxbridge1$newModuleReader() noexcept {
  ::std::unique_ptr<::wasm_shims::ModuleReader> (*newModuleReader$)() = ::wasm_shims::newModuleReader;
  return newModuleReader$().release();
}

void wasm_shims$cxxbridge1$ModuleReader$setDebugInfo(::wasm_shims::ModuleReader &self, bool debug) noexcept {
  void (::wasm_shims::ModuleReader::*setDebugInfo$)(bool) = &::wasm_shims::ModuleReader::setDebugInfo;
  (self.*setDebugInfo$)(debug);
}

void wasm_shims$cxxbridge1$ModuleReader$setDwarf(::wasm_shims::ModuleReader &self, bool dwarf) noexcept {
  void (::wasm_shims::ModuleReader::*setDwarf$)(bool) = &::wasm_shims::ModuleReader::setDwarf;
  (self.*setDwarf$)(dwarf);
}

::rust::repr::PtrLen wasm_shims$cxxbridge1$ModuleReader$readText(::wasm_shims::ModuleReader &self, ::std::string &filename, ::wasm_shims::Module &wasm) noexcept {
  void (::wasm_shims::ModuleReader::*readText$)(::std::string &, ::wasm_shims::Module &) = &::wasm_shims::ModuleReader::readText;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        (self.*readText$)(filename, wasm);
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::rust::repr::PtrLen wasm_shims$cxxbridge1$ModuleReader$readBinary(::wasm_shims::ModuleReader &self, ::std::string &filename, ::wasm_shims::Module &wasm, ::std::string &sourceMapFilename) noexcept {
  void (::wasm_shims::ModuleReader::*readBinary$)(::std::string &, ::wasm_shims::Module &, ::std::string &) = &::wasm_shims::ModuleReader::readBinary;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        (self.*readBinary$)(filename, wasm, sourceMapFilename);
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::rust::repr::PtrLen wasm_shims$cxxbridge1$ModuleReader$read(::wasm_shims::ModuleReader &self, ::std::string &filename, ::wasm_shims::Module &wasm, ::std::string &sourceMapFilename) noexcept {
  void (::wasm_shims::ModuleReader::*read$)(::std::string &, ::wasm_shims::Module &, ::std::string &) = &::wasm_shims::ModuleReader::read;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        (self.*read$)(filename, wasm, sourceMapFilename);
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::wasm_shims::ModuleWriter *wasm_shims$cxxbridge1$newModuleWriter() noexcept {
  ::std::unique_ptr<::wasm_shims::ModuleWriter> (*newModuleWriter$)() = ::wasm_shims::newModuleWriter;
  return newModuleWriter$().release();
}

void wasm_shims$cxxbridge1$ModuleWriter$setDebugInfo(::wasm_shims::ModuleWriter &self, bool debug) noexcept {
  void (::wasm_shims::ModuleWriter::*setDebugInfo$)(bool) = &::wasm_shims::ModuleWriter::setDebugInfo;
  (self.*setDebugInfo$)(debug);
}

void wasm_shims$cxxbridge1$ModuleWriter$setSourceMapFilename(::wasm_shims::ModuleWriter &self, ::std::string &source_map_filename) noexcept {
  void (::wasm_shims::ModuleWriter::*setSourceMapFilename$)(::std::string &) = &::wasm_shims::ModuleWriter::setSourceMapFilename;
  (self.*setSourceMapFilename$)(source_map_filename);
}

void wasm_shims$cxxbridge1$ModuleWriter$setSourceMapUrl(::wasm_shims::ModuleWriter &self, ::std::string &source_map_url) noexcept {
  void (::wasm_shims::ModuleWriter::*setSourceMapUrl$)(::std::string &) = &::wasm_shims::ModuleWriter::setSourceMapUrl;
  (self.*setSourceMapUrl$)(source_map_url);
}

::rust::repr::PtrLen wasm_shims$cxxbridge1$ModuleWriter$writeText(::wasm_shims::ModuleWriter &self, ::wasm_shims::Module &wasm, ::std::string &filename) noexcept {
  void (::wasm_shims::ModuleWriter::*writeText$)(::wasm_shims::Module &, ::std::string &) = &::wasm_shims::ModuleWriter::writeText;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        (self.*writeText$)(wasm, filename);
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::rust::repr::PtrLen wasm_shims$cxxbridge1$ModuleWriter$writeBinary(::wasm_shims::ModuleWriter &self, ::wasm_shims::Module &wasm, ::std::string &filename) noexcept {
  void (::wasm_shims::ModuleWriter::*writeBinary$)(::wasm_shims::Module &, ::std::string &) = &::wasm_shims::ModuleWriter::writeBinary;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        (self.*writeBinary$)(wasm, filename);
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

::std::vector<::std::string> *wasm_shims$cxxbridge1$getRegisteredNames() noexcept {
  ::std::unique_ptr<::std::vector<::std::string>> (*getRegisteredNames$)() = ::wasm_shims::getRegisteredNames;
  return getRegisteredNames$().release();
}

::std::string *wasm_shims$cxxbridge1$getPassDescription(::std::string &name) noexcept {
  ::std::unique_ptr<::std::string> (*getPassDescription$)(::std::string &) = ::wasm_shims::getPassDescription;
  return getPassDescription$(name).release();
}

bool wasm_shims$cxxbridge1$isPassHidden(::std::string &name) noexcept {
  bool (*isPassHidden$)(::std::string &) = ::wasm_shims::isPassHidden;
  return isPassHidden$(name);
}

::wasm_shims::InliningOptions *wasm_shims$cxxbridge1$newInliningOptions() noexcept {
  ::std::unique_ptr<::wasm_shims::InliningOptions> (*newInliningOptions$)() = ::wasm_shims::newInliningOptions;
  return newInliningOptions$().release();
}

void wasm_shims$cxxbridge1$InliningOptions$setAlwaysInlineMaxSize(::wasm_shims::InliningOptions &self, ::std::uint32_t size) noexcept {
  void (::wasm_shims::InliningOptions::*setAlwaysInlineMaxSize$)(::std::uint32_t) = &::wasm_shims::InliningOptions::setAlwaysInlineMaxSize;
  (self.*setAlwaysInlineMaxSize$)(size);
}

void wasm_shims$cxxbridge1$InliningOptions$setOneCallerInlineMaxSize(::wasm_shims::InliningOptions &self, ::std::uint32_t size) noexcept {
  void (::wasm_shims::InliningOptions::*setOneCallerInlineMaxSize$)(::std::uint32_t) = &::wasm_shims::InliningOptions::setOneCallerInlineMaxSize;
  (self.*setOneCallerInlineMaxSize$)(size);
}

void wasm_shims$cxxbridge1$InliningOptions$setFlexibleInlineMaxSize(::wasm_shims::InliningOptions &self, ::std::uint32_t size) noexcept {
  void (::wasm_shims::InliningOptions::*setFlexibleInlineMaxSize$)(::std::uint32_t) = &::wasm_shims::InliningOptions::setFlexibleInlineMaxSize;
  (self.*setFlexibleInlineMaxSize$)(size);
}

void wasm_shims$cxxbridge1$InliningOptions$setAllowFunctionsWithLoops(::wasm_shims::InliningOptions &self, bool allow) noexcept {
  void (::wasm_shims::InliningOptions::*setAllowFunctionsWithLoops$)(bool) = &::wasm_shims::InliningOptions::setAllowFunctionsWithLoops;
  (self.*setAllowFunctionsWithLoops$)(allow);
}

void wasm_shims$cxxbridge1$InliningOptions$setPartialInliningIfs(::wasm_shims::InliningOptions &self, ::std::uint32_t number) noexcept {
  void (::wasm_shims::InliningOptions::*setPartialInliningIfs$)(::std::uint32_t) = &::wasm_shims::InliningOptions::setPartialInliningIfs;
  (self.*setPartialInliningIfs$)(number);
}

::wasm_shims::PassOptions *wasm_shims$cxxbridge1$newPassOptions() noexcept {
  ::std::unique_ptr<::wasm_shims::PassOptions> (*newPassOptions$)() = ::wasm_shims::newPassOptions;
  return newPassOptions$().release();
}

void wasm_shims$cxxbridge1$PassOptions$setValidate(::wasm_shims::PassOptions &self, bool validate) noexcept {
  void (::wasm_shims::PassOptions::*setValidate$)(bool) = &::wasm_shims::PassOptions::setValidate;
  (self.*setValidate$)(validate);
}

void wasm_shims$cxxbridge1$PassOptions$setValidateGlobally(::wasm_shims::PassOptions &self, bool validate) noexcept {
  void (::wasm_shims::PassOptions::*setValidateGlobally$)(bool) = &::wasm_shims::PassOptions::setValidateGlobally;
  (self.*setValidateGlobally$)(validate);
}

void wasm_shims$cxxbridge1$PassOptions$setOptimizeLevel(::wasm_shims::PassOptions &self, ::std::int32_t level) noexcept {
  void (::wasm_shims::PassOptions::*setOptimizeLevel$)(::std::int32_t) = &::wasm_shims::PassOptions::setOptimizeLevel;
  (self.*setOptimizeLevel$)(level);
}

void wasm_shims$cxxbridge1$PassOptions$setShrinkLevel(::wasm_shims::PassOptions &self, ::std::int32_t level) noexcept {
  void (::wasm_shims::PassOptions::*setShrinkLevel$)(::std::int32_t) = &::wasm_shims::PassOptions::setShrinkLevel;
  (self.*setShrinkLevel$)(level);
}

void wasm_shims$cxxbridge1$PassOptions$setInliningOptions(::wasm_shims::PassOptions &self, ::wasm_shims::InliningOptions *inlining) noexcept {
  void (::wasm_shims::PassOptions::*setInliningOptions$)(::std::unique_ptr<::wasm_shims::InliningOptions>) = &::wasm_shims::PassOptions::setInliningOptions;
  (self.*setInliningOptions$)(::std::unique_ptr<::wasm_shims::InliningOptions>(inlining));
}

void wasm_shims$cxxbridge1$PassOptions$setTrapsNeverHappen(::wasm_shims::PassOptions &self, bool ignoreTraps) noexcept {
  void (::wasm_shims::PassOptions::*setTrapsNeverHappen$)(bool) = &::wasm_shims::PassOptions::setTrapsNeverHappen;
  (self.*setTrapsNeverHappen$)(ignoreTraps);
}

void wasm_shims$cxxbridge1$PassOptions$setLowMemoryUnused(::wasm_shims::PassOptions &self, bool memoryUnused) noexcept {
  void (::wasm_shims::PassOptions::*setLowMemoryUnused$)(bool) = &::wasm_shims::PassOptions::setLowMemoryUnused;
  (self.*setLowMemoryUnused$)(memoryUnused);
}

void wasm_shims$cxxbridge1$PassOptions$setFastMath(::wasm_shims::PassOptions &self, bool fastMath) noexcept {
  void (::wasm_shims::PassOptions::*setFastMath$)(bool) = &::wasm_shims::PassOptions::setFastMath;
  (self.*setFastMath$)(fastMath);
}

void wasm_shims$cxxbridge1$PassOptions$setZeroFilledMemory(::wasm_shims::PassOptions &self, bool zeroFilledMemory) noexcept {
  void (::wasm_shims::PassOptions::*setZeroFilledMemory$)(bool) = &::wasm_shims::PassOptions::setZeroFilledMemory;
  (self.*setZeroFilledMemory$)(zeroFilledMemory);
}

void wasm_shims$cxxbridge1$PassOptions$setDebugInfo(::wasm_shims::PassOptions &self, bool debugInfo) noexcept {
  void (::wasm_shims::PassOptions::*setDebugInfo$)(bool) = &::wasm_shims::PassOptions::setDebugInfo;
  (self.*setDebugInfo$)(debugInfo);
}

void wasm_shims$cxxbridge1$PassOptions$setArguments(::wasm_shims::PassOptions &self, ::std::string &key, ::std::string &value) noexcept {
  void (::wasm_shims::PassOptions::*setArguments$)(::std::string &, ::std::string &) = &::wasm_shims::PassOptions::setArguments;
  (self.*setArguments$)(key, value);
}

::wasm_shims::WasmFeatureSet *wasm_shims$cxxbridge1$newFeatureSet() noexcept {
  ::std::unique_ptr<::wasm_shims::WasmFeatureSet> (*newFeatureSet$)() = ::wasm_shims::newFeatureSet;
  return newFeatureSet$().release();
}

void wasm_shims$cxxbridge1$WasmFeatureSet$setMVP(::wasm_shims::WasmFeatureSet &self) noexcept {
  void (::wasm_shims::WasmFeatureSet::*setMVP$)() = &::wasm_shims::WasmFeatureSet::setMVP;
  (self.*setMVP$)();
}

void wasm_shims$cxxbridge1$WasmFeatureSet$setAll(::wasm_shims::WasmFeatureSet &self) noexcept {
  void (::wasm_shims::WasmFeatureSet::*setAll$)() = &::wasm_shims::WasmFeatureSet::setAll;
  (self.*setAll$)();
}

void wasm_shims$cxxbridge1$WasmFeatureSet$set(::wasm_shims::WasmFeatureSet &self, ::std::uint32_t feature, bool val) noexcept {
  void (::wasm_shims::WasmFeatureSet::*set$)(::std::uint32_t, bool) = &::wasm_shims::WasmFeatureSet::set;
  (self.*set$)(feature, val);
}

bool wasm_shims$cxxbridge1$WasmFeatureSet$has(::wasm_shims::WasmFeatureSet const &self, ::wasm_shims::WasmFeatureSet const &features) noexcept {
  bool (::wasm_shims::WasmFeatureSet::*has$)(::wasm_shims::WasmFeatureSet const &) const = &::wasm_shims::WasmFeatureSet::has;
  return (self.*has$)(features);
}

::std::uint32_t wasm_shims$cxxbridge1$WasmFeatureSet$as_int(::wasm_shims::WasmFeatureSet const &self) noexcept {
  ::std::uint32_t (::wasm_shims::WasmFeatureSet::*as_int$)() const = &::wasm_shims::WasmFeatureSet::as_int;
  return (self.*as_int$)();
}

::std::vector<::std::uint32_t> *wasm_shims$cxxbridge1$getFeatureArray() noexcept {
  ::std::unique_ptr<::std::vector<::std::uint32_t>> (*getFeatureArray$)() = ::wasm_shims::getFeatureArray;
  return getFeatureArray$().release();
}

void wasm_shims$cxxbridge1$applyFeatures(::wasm_shims::Module &wasm, ::wasm_shims::WasmFeatureSet *enabled_features, ::wasm_shims::WasmFeatureSet *disabled_features) noexcept {
  void (*applyFeatures$)(::wasm_shims::Module &, ::std::unique_ptr<::wasm_shims::WasmFeatureSet>, ::std::unique_ptr<::wasm_shims::WasmFeatureSet>) = ::wasm_shims::applyFeatures;
  applyFeatures$(wasm, ::std::unique_ptr<::wasm_shims::WasmFeatureSet>(enabled_features), ::std::unique_ptr<::wasm_shims::WasmFeatureSet>(disabled_features));
}

::wasm_shims::PassRunner *wasm_shims$cxxbridge1$newPassRunner(::wasm_shims::Module &wasm) noexcept {
  ::std::unique_ptr<::wasm_shims::PassRunner> (*newPassRunner$)(::wasm_shims::Module &) = ::wasm_shims::newPassRunner;
  return newPassRunner$(wasm).release();
}

::wasm_shims::PassRunner *wasm_shims$cxxbridge1$newPassRunnerWithOptions(::wasm_shims::Module &wasm, ::wasm_shims::PassOptions *options) noexcept {
  ::std::unique_ptr<::wasm_shims::PassRunner> (*newPassRunnerWithOptions$)(::wasm_shims::Module &, ::std::unique_ptr<::wasm_shims::PassOptions>) = ::wasm_shims::newPassRunnerWithOptions;
  return newPassRunnerWithOptions$(wasm, ::std::unique_ptr<::wasm_shims::PassOptions>(options)).release();
}

void wasm_shims$cxxbridge1$PassRunner$add(::wasm_shims::PassRunner &self, ::std::string &pass_name) noexcept {
  void (::wasm_shims::PassRunner::*add$)(::std::string &) = &::wasm_shims::PassRunner::add;
  (self.*add$)(pass_name);
}

void wasm_shims$cxxbridge1$PassRunner$addDefaultOptimizationPasses(::wasm_shims::PassRunner &self) noexcept {
  void (::wasm_shims::PassRunner::*addDefaultOptimizationPasses$)() = &::wasm_shims::PassRunner::addDefaultOptimizationPasses;
  (self.*addDefaultOptimizationPasses$)();
}

void wasm_shims$cxxbridge1$PassRunner$run(::wasm_shims::PassRunner &self) noexcept {
  void (::wasm_shims::PassRunner::*run$)() = &::wasm_shims::PassRunner::run;
  (self.*run$)();
}

bool wasm_shims$cxxbridge1$passRemovesDebugInfo(::std::string &name) noexcept {
  bool (*passRemovesDebugInfo$)(::std::string &) = ::wasm_shims::passRemovesDebugInfo;
  return passRemovesDebugInfo$(name);
}

bool wasm_shims$cxxbridge1$checkInliningOptionsDefaults(::wasm_shims::InliningOptions *inlining_options) noexcept {
  bool (*checkInliningOptionsDefaults$)(::std::unique_ptr<::wasm_shims::InliningOptions>) = ::wasm_shims::checkInliningOptionsDefaults;
  return checkInliningOptionsDefaults$(::std::unique_ptr<::wasm_shims::InliningOptions>(inlining_options));
}

bool wasm_shims$cxxbridge1$checkPassOptionsDefaults(::wasm_shims::PassOptions *pass_options) noexcept {
  bool (*checkPassOptionsDefaults$)(::std::unique_ptr<::wasm_shims::PassOptions>) = ::wasm_shims::checkPassOptionsDefaults;
  return checkPassOptionsDefaults$(::std::unique_ptr<::wasm_shims::PassOptions>(pass_options));
}

bool wasm_shims$cxxbridge1$checkPassOptionsDefaultsOs(::wasm_shims::PassOptions *pass_options) noexcept {
  bool (*checkPassOptionsDefaultsOs$)(::std::unique_ptr<::wasm_shims::PassOptions>) = ::wasm_shims::checkPassOptionsDefaultsOs;
  return checkPassOptionsDefaultsOs$(::std::unique_ptr<::wasm_shims::PassOptions>(pass_options));
}
} // extern "C"
} // namespace wasm_shims

extern "C" {
static_assert(::rust::detail::is_complete<::wasm_shims::Module>::value, "definition of Module is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::Module>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::Module>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$Module$null(::std::unique_ptr<::wasm_shims::Module> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::Module>();
}
void cxxbridge1$unique_ptr$wasm_shims$Module$raw(::std::unique_ptr<::wasm_shims::Module> *ptr, ::wasm_shims::Module *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::Module>(raw);
}
::wasm_shims::Module const *cxxbridge1$unique_ptr$wasm_shims$Module$get(::std::unique_ptr<::wasm_shims::Module> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::Module *cxxbridge1$unique_ptr$wasm_shims$Module$release(::std::unique_ptr<::wasm_shims::Module> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$Module$drop(::std::unique_ptr<::wasm_shims::Module> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::Module>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::ModuleReader>::value, "definition of ModuleReader is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::ModuleReader>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::ModuleReader>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$ModuleReader$null(::std::unique_ptr<::wasm_shims::ModuleReader> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::ModuleReader>();
}
void cxxbridge1$unique_ptr$wasm_shims$ModuleReader$raw(::std::unique_ptr<::wasm_shims::ModuleReader> *ptr, ::wasm_shims::ModuleReader *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::ModuleReader>(raw);
}
::wasm_shims::ModuleReader const *cxxbridge1$unique_ptr$wasm_shims$ModuleReader$get(::std::unique_ptr<::wasm_shims::ModuleReader> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::ModuleReader *cxxbridge1$unique_ptr$wasm_shims$ModuleReader$release(::std::unique_ptr<::wasm_shims::ModuleReader> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$ModuleReader$drop(::std::unique_ptr<::wasm_shims::ModuleReader> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::ModuleReader>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::ModuleWriter>::value, "definition of ModuleWriter is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::ModuleWriter>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::ModuleWriter>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$ModuleWriter$null(::std::unique_ptr<::wasm_shims::ModuleWriter> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::ModuleWriter>();
}
void cxxbridge1$unique_ptr$wasm_shims$ModuleWriter$raw(::std::unique_ptr<::wasm_shims::ModuleWriter> *ptr, ::wasm_shims::ModuleWriter *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::ModuleWriter>(raw);
}
::wasm_shims::ModuleWriter const *cxxbridge1$unique_ptr$wasm_shims$ModuleWriter$get(::std::unique_ptr<::wasm_shims::ModuleWriter> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::ModuleWriter *cxxbridge1$unique_ptr$wasm_shims$ModuleWriter$release(::std::unique_ptr<::wasm_shims::ModuleWriter> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$ModuleWriter$drop(::std::unique_ptr<::wasm_shims::ModuleWriter> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::ModuleWriter>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::InliningOptions>::value, "definition of InliningOptions is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::InliningOptions>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::InliningOptions>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$InliningOptions$null(::std::unique_ptr<::wasm_shims::InliningOptions> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::InliningOptions>();
}
void cxxbridge1$unique_ptr$wasm_shims$InliningOptions$raw(::std::unique_ptr<::wasm_shims::InliningOptions> *ptr, ::wasm_shims::InliningOptions *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::InliningOptions>(raw);
}
::wasm_shims::InliningOptions const *cxxbridge1$unique_ptr$wasm_shims$InliningOptions$get(::std::unique_ptr<::wasm_shims::InliningOptions> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::InliningOptions *cxxbridge1$unique_ptr$wasm_shims$InliningOptions$release(::std::unique_ptr<::wasm_shims::InliningOptions> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$InliningOptions$drop(::std::unique_ptr<::wasm_shims::InliningOptions> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::InliningOptions>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::PassOptions>::value, "definition of PassOptions is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::PassOptions>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::PassOptions>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$PassOptions$null(::std::unique_ptr<::wasm_shims::PassOptions> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::PassOptions>();
}
void cxxbridge1$unique_ptr$wasm_shims$PassOptions$raw(::std::unique_ptr<::wasm_shims::PassOptions> *ptr, ::wasm_shims::PassOptions *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::PassOptions>(raw);
}
::wasm_shims::PassOptions const *cxxbridge1$unique_ptr$wasm_shims$PassOptions$get(::std::unique_ptr<::wasm_shims::PassOptions> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::PassOptions *cxxbridge1$unique_ptr$wasm_shims$PassOptions$release(::std::unique_ptr<::wasm_shims::PassOptions> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$PassOptions$drop(::std::unique_ptr<::wasm_shims::PassOptions> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::PassOptions>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::WasmFeatureSet>::value, "definition of WasmFeatureSet is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::WasmFeatureSet>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::WasmFeatureSet>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$WasmFeatureSet$null(::std::unique_ptr<::wasm_shims::WasmFeatureSet> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::WasmFeatureSet>();
}
void cxxbridge1$unique_ptr$wasm_shims$WasmFeatureSet$raw(::std::unique_ptr<::wasm_shims::WasmFeatureSet> *ptr, ::wasm_shims::WasmFeatureSet *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::WasmFeatureSet>(raw);
}
::wasm_shims::WasmFeatureSet const *cxxbridge1$unique_ptr$wasm_shims$WasmFeatureSet$get(::std::unique_ptr<::wasm_shims::WasmFeatureSet> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::WasmFeatureSet *cxxbridge1$unique_ptr$wasm_shims$WasmFeatureSet$release(::std::unique_ptr<::wasm_shims::WasmFeatureSet> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$WasmFeatureSet$drop(::std::unique_ptr<::wasm_shims::WasmFeatureSet> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::WasmFeatureSet>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::wasm_shims::PassRunner>::value, "definition of PassRunner is required");
static_assert(sizeof(::std::unique_ptr<::wasm_shims::PassRunner>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::wasm_shims::PassRunner>) == alignof(void *), "");
void cxxbridge1$unique_ptr$wasm_shims$PassRunner$null(::std::unique_ptr<::wasm_shims::PassRunner> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::PassRunner>();
}
void cxxbridge1$unique_ptr$wasm_shims$PassRunner$raw(::std::unique_ptr<::wasm_shims::PassRunner> *ptr, ::wasm_shims::PassRunner *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::wasm_shims::PassRunner>(raw);
}
::wasm_shims::PassRunner const *cxxbridge1$unique_ptr$wasm_shims$PassRunner$get(::std::unique_ptr<::wasm_shims::PassRunner> const &ptr) noexcept {
  return ptr.get();
}
::wasm_shims::PassRunner *cxxbridge1$unique_ptr$wasm_shims$PassRunner$release(::std::unique_ptr<::wasm_shims::PassRunner> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$wasm_shims$PassRunner$drop(::std::unique_ptr<::wasm_shims::PassRunner> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::wasm_shims::PassRunner>::value>{}(ptr);
}
} // extern "C"
