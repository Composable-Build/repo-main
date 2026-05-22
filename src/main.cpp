#include <iostream>
#include <dlfcn.h>
#include <filesystem>

#ifdef __APPLE__
#define LIB_EXTENSION ".dylib"
#elif __linux__
#define LIB_EXTENSION ".so"
#else
#error Platform not defined
#endif

namespace fs = std::filesystem;

void try_load_lib(const fs::path& p) {
    void* h = dlopen(p.c_str(), RTLD_NOW);
    if (!h) { std::cerr << "  [ERR] " << dlerror() << "\n"; return; }
    auto fn = (void(*)()) dlsym(h, "plugin_print");
    if (fn) { std::cout << "  [OK] "; fn(); }
    else std::cerr << "  [WARN] plugin_print not found in " << p << "\n";
    dlclose(h);
}

void try_run_bin(const fs::path& p) {
    std::cout << "  [RUN] " << p.string() << "\n";
    std::system(p.c_str());
}

int main() {
    std::cout << "=== main-demo ===\n\n-- libs --\n";
    if (fs::exists("libs"))
        for (auto& e : fs::directory_iterator("libs"))
            //if (e.path().extension() == ".so") try_load_lib(e.path());
            //if (e.path().extension() == ".dylib") try_load_lib(e.path());
            if (e.path().extension() == LIB_EXTENSION) try_load_lib(e.path());

    std::cout << "\n-- binaries --\n";
    if (fs::exists("bin"))
        for (auto& e : fs::directory_iterator("bin"))
            if (fs::is_regular_file(e.path())) try_run_bin(e.path());

    return 0;
}
