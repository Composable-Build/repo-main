#include <catch2/catch_test_macros.hpp>
#include <dlfcn.h>
#include <filesystem>
#include "test_config.h"
namespace fs = std::filesystem;

TEST_CASE("libs directory exists", "[setup]") {
    REQUIRE(fs::exists("libs"));
}
TEST_CASE("each .so loads without error", "[dlopen]") {
    if (!fs::exists("libs")) return;
    for (auto& e : fs::directory_iterator("libs")) {
        if (e.path().extension() != ".so") continue;
        void* h = dlopen(e.path().c_str(), RTLD_NOW);
        INFO("failed to load: " << e.path());
        REQUIRE(h != nullptr);
        dlclose(h);
    }
}
TEST_CASE("flag test", "[flag]") {
    REQUIRE(TEST_SHOULD_FAIL == 0);
}
