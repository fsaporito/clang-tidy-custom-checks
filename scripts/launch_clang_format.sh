#!/usr/bin/env bash

if [ "$1" == "" ] || [ $# -gt 1 ]; then
  echo "Usage $0 <path-to-source-repo>"
  exit 1
fi
working_path="$1"

pushd .

cd ${working_path}

find . \( -name '*.cpp' -o -name '*.c' -o -name '*.cc' -o -name '*.h' -o -name '*.hpp' \) -not -path "./build/*" -exec clang-format --style=file -i {} +

popd