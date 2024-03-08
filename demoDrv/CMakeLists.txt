cmake_minimum_required(VERSION 3.1)

set(API_ROOT "$ENV{API_ROOT}" CACHE FILEPATH "directory of the WinCC_OA API installation")
include(${API_ROOT}/CMakeDefines.txt)

project(demoDrv
  VERSION 0.1.0
)

include(../cmake/packaging.cmake)
include(../cmake/testing.cmake)

set(TARGET WCCOAdemo)

set(SOURCES
demoMain.cxx
)

set(OBJLIB_SOURCES
demoAlertService.cxx
demoConnection.cxx
demoDrv.cxx
demoHWMapper.cxx
demoHWService.cxx
demoResources.cxx
demoTrans.cxx
)

if ( WIN32 )
  set (SOURCES ${SOURCES} VersInfo.rc)
endif()

add_library(${TARGET}Lib OBJECT ${OBJLIB_SOURCES})
add_driver(${TARGET} ${SOURCES} $<TARGET_OBJECTS:${TARGET}Lib>)

get_target_property(${TARGET}_INCLUDES ${TARGET} INCLUDE_DIRECTORIES)
set_target_properties(${TARGET}Lib PROPERTIES INCLUDE_DIRECTORIES "${${TARGET}_INCLUDES}")

add_subdirectory(tests)

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)
