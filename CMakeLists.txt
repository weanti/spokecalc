project(spokecalc)

find_package( FLTK REQUIRED )

include_directories( ${FLTK_INCLUDE_DIR} )
link_directories( ${FLTK_LIBRARY_DIR} )

add_executable( ${PROJECT_NAME} spokecalc.cpp )

target_link_libraries( ${PROJECT_NAME} fltk )
