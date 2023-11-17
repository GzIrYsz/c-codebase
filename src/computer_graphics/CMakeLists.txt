file(GLOB SOURCES ./*.c)
file(GLOB HEADERS ./*.h)

add_library(cg STATIC ${SOURCES} ${HEADERS})
