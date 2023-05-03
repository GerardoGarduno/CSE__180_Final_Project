#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "robotpatrol::navigator" for configuration ""
set_property(TARGET robotpatrol::navigator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(robotpatrol::navigator PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libnavigator.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS robotpatrol::navigator )
list(APPEND _IMPORT_CHECK_FILES_FOR_robotpatrol::navigator "${_IMPORT_PREFIX}/lib/libnavigator.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
