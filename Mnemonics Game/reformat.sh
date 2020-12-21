#!/bin/sh

find -iname "*.cpp" -o -iname "*.h" | xargs clang-format -i -fallback-style=none
