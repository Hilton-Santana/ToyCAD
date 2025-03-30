if (TARGET triangle)
	return()
endif()

include(FetchContent)

FetchContent_Declare(triangle
      GIT_REPOSITORY "https://github.com/Hilton-Santana/compgeom-triangle.git"
			GIT_TAG master
)

FetchContent_MakeAvailable(triangle)