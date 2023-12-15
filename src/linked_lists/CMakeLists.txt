file(GLOB SOURCES ./*.c)
file(GLOB HEADERS ./*.h)

add_library(ll SHARED ${SOURCES} ${HEADERS})