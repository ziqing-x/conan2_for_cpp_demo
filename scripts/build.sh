#!/bin/bash 

SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=${SCRIPTS_DIR}/..
PROFILE_FOR_LOCAL=${PROJECT_DIR}/profiles/pc
PROFILE_FOR_TARGET=${PROJECT_DIR}/profiles/pc
BUILD_DIR=${PROJECT_DIR}/build

CheckEnv() {
    if command -v conan &> /dev/null; then
        echo "Env is OK"
    else
        echo "Please run 'setup_env.sh' first"
        exit 1
    fi
}

Usage() {
    echo "Usage: $0 [-b|-c] # -b: build, -c: clean"
    echo "Example: $0 -b"
    echo "Example: $0 -c"
}

Build() {
    # 使用 grep 和 awk 提取 build_type 的值
    BUILD_TYPE=$(grep "^build_type=" "${PROFILE_FOR_TARGET}" | awk -F= '{print $2}')
    # 判断是否使用 cmake_layout
    if grep -q "cmake_layout" "${PROJECT_DIR}/conanfile.txt"; then
        conan install "${PROJECT_DIR}" \
              --build missing \
              -pr:b=${PROFILE_FOR_LOCAL} \
              -pr:h=${PROFILE_FOR_TARGET}
        source ${BUILD_DIR}/${BUILD_TYPE}/generators/conanbuild.sh
        cmake -B ${BUILD_DIR} \
              -DENABLE_STATIC_ANALYSIS=OFF \
              -DCMAKE_TOOLCHAIN_FILE=${BUILD_DIR}/${BUILD_TYPE}/generators/conan_toolchain.cmake \
              -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
              ${PROJECT_DIR} || exit
    else
        conan install ${PROJECT_DIR} \
              --output-folder=${BUILD_DIR} \
              --build missing \
              -pr:b=${PROFILE_FOR_LOCAL} \
              -pr:h=${PROFILE_FOR_TARGET}
        source ${BUILD_DIR}/conanbuild.sh
        cmake -B ${BUILD_DIR} \
              -DENABLE_STATIC_ANALYSIS=OFF \
              -DCMAKE_TOOLCHAIN_FILE=${BUILD_DIR}/conan_toolchain.cmake \
              -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
              ${PROJECT_DIR} || exit
    fi
    cmake --build ${BUILD_DIR} --parallel
}

Clean() {
    rm -rf ${BUILD_DIR}
}

if [ $# -ne 1 ]; then
    Usage
    exit 1
fi

if [ "$1" == "-b" ] ; then
    Build 
elif [ "$1" == "-c" ]; then
    Clean
else
    Usage
    exit 1
fi

exit 0

