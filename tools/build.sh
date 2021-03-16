#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $0); pwd)
ROOT_DIR=${SCRIPT_DIR}/..
PROJECT_DIRS=(
  $ROOT_DIR/osc/pulse/platform/minilogue-xd
)

for project_dir in ${PROJECT_DIRS[@]}; do
  echo Build $project_dir
  cd $project_dir
  make && make check
done
