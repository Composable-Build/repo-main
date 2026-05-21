#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build && cmake --build build
mkdir -p libs bin
cp ../repo-lib1/build/libplugin_one.dylib libs/ 2>/dev/null || echo "[warn] missing repo-lib1 build"
cp ../repo-lib2/build/libplugin_two.dylib libs/ 2>/dev/null || echo "[warn] missing repo-lib2 build"
cp ../repo-bin1/build/binary1-demo  bin/  2>/dev/null || echo "[warn] missing repo-bin1 build"
cp ../repo-bin2/build/binary2-demo  bin/  2>/dev/null || echo "[warn] missing repo-bin2 build"
./build/main-demo
