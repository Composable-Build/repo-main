#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build && cmake --build build
mkdir -p libs bin
cp ../repo-lib1/build/libplugin_one.so libs/ 2>/dev/null || echo "[warn] missing repo-lib1 build"
cp ../repo-lib2/build/libplugin_two.so libs/ 2>/dev/null || echo "[warn] missing repo-lib2 build"
cp ../repo-binaries/build/binary-demo  bin/  2>/dev/null || echo "[warn] missing repo-binaries build"
./build/main-demo
