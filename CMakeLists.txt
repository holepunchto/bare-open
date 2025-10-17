cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_open C)

add_bare_module(bare_open)

target_sources(
  ${bare_open}
  PRIVATE
    binding.c
)

if(APPLE)
  target_sources(
    ${bare_open}
    PRIVATE
      apple.m
  )

  target_link_libraries(
    ${bare_open}
    PUBLIC
      "-framework AppKit"
  )
endif()

if(LINUX)
  target_sources(
    ${bare_open}
    PRIVATE
      linux.c
  )
endif()

if(WIN32)
  target_sources(
    ${bare_open}
    PRIVATE
      win32.c
  )
endif()
