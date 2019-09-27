cmake_minimum_required(VERSION 3.13.0)

include(CMakeParseArguments)

function(generate_libuc2_version)
  set(options FAST)
  set(oneValueArgs VERSION_FILE HEADER_TEMPLATE HEADER_OUT)
  set(multiValueArgs)
  cmake_parse_arguments(GEN
                        "${options}"
                        "${oneValueArgs}"
                        "${multiValueArgs}"
                        ${ARGN})

  set(LIB_VERSION "0.0.0")
  set(LIB_VERSION_MAJOR "0")
  set(LIB_VERSION_MINOR "0")
  set(LIB_VERSION_PATCH "0")

  if(EXISTS ${GEN_VERSION_FILE})
    file(READ ${GEN_VERSION_FILE} LIB_VERSION)
    string(STRIP ${LIB_VERSION} LIB_VERSION)
    message(STATUS "LIB_VERSION: " ${LIB_VERSION})
  else()
    message(
      WARNING "'${GEN_VERSION_FILE}' does not exist, unable to get app version."
      )
  endif()

  string(REPLACE "."
                 ";"
                 VERSION_LIST
                 ${LIB_VERSION})
  list(GET VERSION_LIST 0 LIB_VERSION_MAJOR)
  list(GET VERSION_LIST 1 LIB_VERSION_MINOR)
  list(GET VERSION_LIST 2 LIB_VERSION_PATCH)

  set(LIB_VERSION ${LIB_VERSION} PARENT_SCOPE)
  set(LIB_VERSION_MAJOR ${LIB_VERSION_MAJOR} PARENT_SCOPE)
  set(LIB_VERSION_MINOR ${LIB_VERSION_MINOR} PARENT_SCOPE)
  set(LIB_VERSION_PATCH ${LIB_VERSION_PATCH} PARENT_SCOPE)

  configure_file(${GEN_HEADER_TEMPLATE} ${GEN_HEADER_OUT})
endfunction()
