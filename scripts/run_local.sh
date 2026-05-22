#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build -DVERSION_MAJOR=0 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -DVERSION_BUILD=0
cmake --build build
mkdir -p libs bin
cp ../repo-lib1/build/libplugin_one.so libs/ 2>/dev/null || echo "[warn] missing repo-lib1"
cp ../repo-lib2/build/libplugin_two.so libs/ 2>/dev/null || echo "[warn] missing repo-lib2"
cp ../repo-bin1/build/binary_one       bin/  2>/dev/null || echo "[warn] missing repo-bin1"
cp ../repo-bin2/build/binary_two       bin/  2>/dev/null || echo "[warn] missing repo-bin2"
chmod +x bin/* 2>/dev/null || true
cmake --build build --target tests_main
./build/tests_main
./build/main-demo
