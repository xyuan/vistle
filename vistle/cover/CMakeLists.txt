set(CMAKE_MODULE_PATH "$ENV{COVISEDIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(COVER)
if (NOT COVER_FOUND)
   message("COVER not found - not building COVER plugins")
   return()
endif()
covise_create_using()

message("Building COVER plugins for ARCHSUFFIX ${COVISE_ARCHSUFFIX}, destination is ${COVISE_DESTDIR}")

add_subdirectory(Vistle)
add_subdirectory(CompositorIceT)
add_subdirectory(VncClient)
add_subdirectory(VncServer)
