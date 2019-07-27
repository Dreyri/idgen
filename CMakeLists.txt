cmake_minimum_required(VERSION 3.10)

project(idgen VERSION "0.1.0" LANGUAGES CXX)

option(BUILD_TESTS "Build idgen tests" OFF)

set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

include(CMakePackageConfigHelpers)

find_package(nameof REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_link_libraries(${PROJECT_NAME} INTERFACE nameof::nameof)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

set(IDGEN_PC ${CMAKE_CURRENT_BINARY_DIR}/idgen.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/idgen.pc.cmakein ${IDGEN_PC} @ONLY)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Config)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/${PROJECT_NAME})

install(
  EXPORT ${PROJECT_NAME}Config
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME})

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
  DESTINATION .)

install(
  FILES ${IDGEN_PC}
  DESTINATION "${INSTALL_PKGCONFIG_DIR}")
