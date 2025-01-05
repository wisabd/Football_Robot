
include_directories(${CMAKE_SOURCE_DIR}/include)


set(ARGSUB_SRC gsub.c)
set(ARGSUB_UTIL_SRC gsubUtil.c)
set(ARGSUB_LITE_SRC gsub_lite.c)

add_library(ARgsub SHARED ${ARGSUB_SRC})
add_library(ARgsubUtil SHARED ${ARGSUB_UTIL_SRC})
add_library(ARgsub_lite SHARED ${ARGSUB_LITE_SRC})
