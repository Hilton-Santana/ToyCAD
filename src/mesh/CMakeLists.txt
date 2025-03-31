set(source
    delaunay.cpp
    mesh.cpp
    transfinbilinear.cpp
    transfintriilinear.cpp)

set(exports
    delaunay.h
    meshgenerator.h
    mesh.h
    transfinbilinear.h
    transfintrilinear.h)

target_sources(toycad  
               PRIVATE ${source}
               PUBLIC FILE_SET HEADERS FILES ${exports})