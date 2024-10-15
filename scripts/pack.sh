#!/bin/bash

SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=${SCRIPTS_DIR}/..
BUILD_DIR=${PROJECT_DIR}/build


${SCRIPTS_DIR}/build.sh -b
pushd ${BUILD_DIR}
cpack || exit 1
popd
exit 0
