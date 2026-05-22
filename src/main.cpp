#include <iostream>
#include <dlfcn.h>
#include <filesystem>
#include <cstdio>
#include <string>
#include "version.h"
namespace fs = std::filesystem;

void load_lib(const fs::path& p) {
    void* h = dlopen(p.c_str(), RTLD_NOW);
    if (!h) { std::cerr << "  [ERR] " << dlerror() << "\n"; return; }
    auto name_fn    = (const char*(*)()) dlsym(h, "plugin_name");
    auto version_fn = (const char*(*)()) dlsym(h, "plugin_version");
    auto print_fn   = (void(*)())        dlsym(h, "plugin_print");
    std::cout << "  [OK] "
              << (name_fn    ? name_fn()    : p.filename().string()) << "  "
              << (version_fn ? version_fn() : "?") << "\n";
    if (print_fn) print_fn();
    dlclose(h);
}

std::string popen_str(const std::string& cmd) {
    FILE* f = popen(cmd.c_str(), "r");
    if (!f) return "?";
    char buf[64] = {};
    fgets(buf, sizeof(buf), f);
    pclose(f);
    std::string s(buf);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}

void run_bin(const fs::path& p) {
    std::string name = popen_str(p.string() + " --name");
    std::string ver  = popen_str(p.string() + " --version");
    std::cout << "  [RUN] " << name << "  " << ver << "\n";
}

int main() {
    std::cout << "=== main-demo " << get_version() << " ===\n\n-- libs --\n";
    if (fs::exists("libs"))
        for (auto& e : fs::directory_iterator("libs"))
            if (e.path().extension() == ".so") load_lib(e.path());
    std::cout << "\n-- binaries --\n";
    if (fs::exists("bin"))
        for (auto& e : fs::directory_iterator("bin"))
            if (fs::is_regular_file(e.path())) run_bin(e.path());
    return 0;
}
