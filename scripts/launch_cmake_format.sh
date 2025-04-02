#!/usr/bin/env bash

if [ "$1" == "" ] || [ $# -gt 1 ]; then
  echo "Usage $0 <path-to-source-repo>"
  exit 1
fi
working_path="$1"

pushd .

cd ${working_path}

find . \( -name '*.cmake' -o -name 'CMakeLists.txt' \) -not -path "./build/*" -exec cmake-format --config-files .cmake-format.yaml --in-place {} +

popd