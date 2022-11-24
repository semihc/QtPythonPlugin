file(GLOB appSrcs *.cc *.cpp)
file(GLOB appHdrs *.h *.hh *.hpp)

# Current test executable name
set(appNm qtpypi_test)


add_executable(${appNm} ${appSrcs})
add_test(NAME ${appNm} COMMAND ${appNm})


target_include_directories(${appNm}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PrjSrc}/qtpypi
)

#-set_property(TARGET ${appNm} PROPERTY ENABLE_EXPORTS 1)

target_link_libraries(${appNm} PUBLIC Qt::Core pybind11::pybind11 GTest::gtest)
