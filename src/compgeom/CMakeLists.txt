set(source
    compgeom.cpp
    point.cpp
    tesselation.cpp)

set(export
    compgeom.h
    point.h
    tesselation.h)

add_library(compgeom SHARED ${source})
target_link_libraries(compgeom PRIVATE predicates)

