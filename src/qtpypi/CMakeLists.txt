file(GLOB libSrcs *.cc *.cpp)
file(GLOB libHdrs *.h *.hh *.hpp)

# Current library name
set(libNm qtpypi)

#-add_library(${libNm} STATIC)
qt_add_plugin(${libNm}
    CLASS_NAME QtPythonPI
)


target_sources(${libNm}
    PRIVATE ${libSrcs}
    PUBLIC FILE_SET HEADERS FILES ${libHdrs}
)

target_include_directories(${libNm}
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    #-${PrjSrc}/base
)

target_link_libraries(${libNm} PUBLIC Qt::Core PRIVATE pybind11::embed)

#[[
install(
  TARGETS ${libNm}
  EXPORT ${TARGETS_EXPORT_NAME}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCDIR}
)
#]]