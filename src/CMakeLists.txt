set(source
    color.cpp
    curvecollector.cpp
    glcanvas.cpp
    grid.cpp
    main.cpp
    myapp.cpp
    mymodel.cpp
    region.cpp)

set(export
    color.h
    curvecollector.h
    glcanvas.h
    grid.h
    mesh
    meshedge.ui
    meshface.ui
    myapp.h
    region.h)
  
set (sub_dirs
     compgeom
     curves
     mesh)

target_sources(toycad  
               PRIVATE ${source}
               PUBLIC FILE_SET HEADERS FILES ${exports})

# Add each subdirectory
foreach(dir ${sub_dirs})
    add_subdirectory(${dir})
endforeach()
