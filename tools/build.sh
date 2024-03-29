#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $0); pwd)
ROOT_DIR=${SCRIPT_DIR}/..
PROJECT_DIRS=(
  $ROOT_DIR/osc/pulse/platform/minilogue-xd
  $ROOT_DIR/osc/pulse/platform/nutekt-digital
  $ROOT_DIR/osc/pulse/platform/prologue
  $ROOT_DIR/osc/noise/platform/minilogue-xd
  $ROOT_DIR/osc/noise/platform/nutekt-digital
  $ROOT_DIR/osc/noise/platform/prologue
  $ROOT_DIR/osc/pokegold/platform/minilogue-xd
  $ROOT_DIR/osc/pokegold/platform/nutekt-digital
  $ROOT_DIR/osc/pokegold/platform/prologue
)

stat=0

for project_dir in ${PROJECT_DIRS[@]}; do
  echo Build $project_dir
  cd $project_dir
  make && make check
  stat=$(($stat | $?))
done

exit $stat
