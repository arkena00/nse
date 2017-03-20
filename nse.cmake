function(project_nse_release)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
  )

  set(INCLUD_DIRS 
    include
    ../nds/include
  )
  include_directories(${INCLUD_DIRS})

  set(SRC 
    source/main.cpp
    source/nse/encoder.cpp
    source/nse/entity.cpp
    source/nse/file.cpp
  )
  add_executable( nse_release ${SRC})
  set_target_properties( nse_release 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Projet/nk/nse/bin"
    LIBRARY_OUTPUT_DIRECTORY "C:/Projet/nk/nse/bin"
    RUNTIME_OUTPUT_DIRECTORY "C:/Projet/nk/nse/bin"
    OUTPUT_NAME  "nse"
  )
endfunction(project_nse_release)
project_nse_release()
