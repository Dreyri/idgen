set(TESTS
  combination
  )

find_package(Catch2 REQUIRED)

function(make_test target)
  string(CONCAT target_src ${target} ".cpp")
  add_executable(${target} ${target_src})
  target_link_libraries(${target} PRIVATE ${CMAKE_PROJECT_NAME} Catch2::Catch2)
  add_test(NAME ${target} COMMAND ${target})
endfunction()

foreach(t ${TESTS})
  make_test(${t})
endforeach()
