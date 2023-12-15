file(GLOB SOURCES ./*.c)
file(GLOB HEADERS ./*.h)

add_library(base SHARED ${SOURCES} ${HEADERS})