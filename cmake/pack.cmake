# APP_NAME: 对外的名称，可以和进程名一致
# PKG_NAME: 包名, 用公司域名倒过来 + app_name保证唯一性
# VERSION： 版本名，X.Y.Z
# 1、X为主版本，不需要向下兼；
# 2、Y为次版本，向下兼容，属于增量升级, 例如增加新功能，新接口；
# 3、Z为修订版本, 向下兼容, 比如修复某个函数里的某个逻辑;

set(VERSION "1.0.0")
set(DESCRIPTION "测试包")
set(APP_NAME "${PROJECT_NAME}")
set(PKG_NAME "cn.xxx.${APP_NAME}")
set(ARCH "amd64")
set(APP_ROOT_DIR "/opt/${PKG_NAME}")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCH})
set(CPACK_PACKAGE_NAME "${PKG_NAME}")
set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_CONTACT "jassimxiong@gmail.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "jassimxiong@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${DESCRIPTION}")
set(CPACK_PACKAGING_INSTALL_PREFIX "${APP_ROOT_DIR}")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${TOP}/postinst")

configure_file(${TOP}/service/app.service ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.service @ONLY)

# bin
install(
    PROGRAMS ${CMAKE_BINARY_DIR}/bin/${APP_NAME}
    DESTINATION ${APP_ROOT_DIR}/bin
)
# config
install(
    FILES ${TOP}/config/config.yaml
    DESTINATION ${APP_ROOT_DIR}/config
)
# service
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.service
    DESTINATION /usr/lib/systemd/system
)
include(CPack)
