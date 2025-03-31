set(source
    circlearc.cpp
    circle.cpp
    cubicbezier.cpp
    curve.cpp
    line.cpp
    polyline.cpp
    quadbezier.cpp)

set(export
    circlearc.h
    circle.h
    cubicbezier.h
    curve.h
    line.h
    polyline.h
    quadbezier.h)

target_sources(cad 
               PRIVATE ${source}
               PUBLIC FILE_SET HEADERS FILES ${exports})