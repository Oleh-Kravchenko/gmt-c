CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(gmt-c)

INCLUDE(CMakePackageConfigHelpers)
INCLUDE(GenerateExportHeader)
INCLUDE(GNUInstallDirs)

FIND_PACKAGE(cmake-version4git 0.0 QUIET)
IF(NOT cmake-version4git_FOUND)
	INCLUDE(3rdparty/cmake-version4git/cmake/cmake-version4git.cmake)
ENDIF()

PROJECT_VERSION_FROM_GIT()
ADD_DEFINITIONS(${PROJECT_VERSION4GIT_CFLAGS})

ADD_LIBRARY(gmt SHARED
include/gmt/gmt.h
include/platform.h
include/sha1.h
source/gmt.c
source/sha1.c
$<IF:$<PLATFORM_ID:Windows>,source/win32.c,source/unix.c>
${CMAKE_CURRENT_BINARY_DIR}/gmt/gmt_export.h)

GENERATE_EXPORT_HEADER(gmt EXPORT_FILE_NAME gmt/gmt_export.h)

TARGET_INCLUDE_DIRECTORIES(gmt
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${PROJECT_VERSION}>)

SET_TARGET_PROPERTIES(gmt PROPERTIES
VERSION
	"${PROJECT_VERSION}"
SOVERSION
	"${PROJECT_VERSION_MAJOR}")

ADD_EXECUTABLE(gmt_test
source/gmt_test.c)

TARGET_LINK_LIBRARIES(gmt_test
PRIVATE
	gmt)

INSTALL(TARGETS gmt EXPORT "${PROJECT_NAME}"
DESTINATION
	${CMAKE_INSTALL_LIBDIR})

INSTALL(TARGETS gmt_test EXPORT "${PROJECT_NAME}"
DESTINATION
	${CMAKE_INSTALL_BINDIR})

INSTALL(DIRECTORY "include/gmt" "${CMAKE_CURRENT_BINARY_DIR}/gmt"
DESTINATION
	"${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${PROJECT_VERSION}"
PATTERN
	"*.h")

WRITE_BASIC_PACKAGE_VERSION_FILE("${PROJECT_NAME}-config-version.cmake"
VERSION
	${PROJECT_VERSION}
COMPATIBILITY
	SameMajorVersion)

CONFIGURE_PACKAGE_CONFIG_FILE("cmake/${PROJECT_NAME}-config.cmake.in" "${PROJECT_NAME}-config.cmake"
INSTALL_DESTINATION
	"${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")

INSTALL(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
DESTINATION
	"${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")

INSTALL(EXPORT "${PROJECT_NAME}"
FILE
	"${PROJECT_NAME}-targets.cmake"
DESTINATION
	"${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}")
