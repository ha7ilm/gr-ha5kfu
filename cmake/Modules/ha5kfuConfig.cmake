INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_HA5KFU ha5kfu)

FIND_PATH(
    HA5KFU_INCLUDE_DIRS
    NAMES ha5kfu/api.h
    HINTS $ENV{HA5KFU_DIR}/include
        ${PC_HA5KFU_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    HA5KFU_LIBRARIES
    NAMES gnuradio-ha5kfu
    HINTS $ENV{HA5KFU_DIR}/lib
        ${PC_HA5KFU_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HA5KFU DEFAULT_MSG HA5KFU_LIBRARIES HA5KFU_INCLUDE_DIRS)
MARK_AS_ADVANCED(HA5KFU_LIBRARIES HA5KFU_INCLUDE_DIRS)

