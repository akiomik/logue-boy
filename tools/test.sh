#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $0); pwd)
ROOT_DIR=${SCRIPT_DIR}/..
PROJECT_DIRS=(
  $ROOT_DIR/osc/pulse/platform/minilogue-xd
  $ROOT_DIR/osc/noise/platform/minilogue-xd
)

for project_dir in ${PROJECT_DIRS[@]}; do
  echo Test $project_dir
  cd $project_dir
  export MAKEFILES=../../test.mk
  make cleantest && make test
done
