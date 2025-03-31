if (TARGET predicates)
	return()
endif()

include(FetchContent)

FetchContent_Declare(predicates
      GIT_REPOSITORY "https://github.com/Hilton-Santana/compgeom-predicates.git"
			GIT_TAG master
)

FetchContent_MakeAvailable(predicates)
