# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CifrasClassicas-JeanArruda_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CifrasClassicas-JeanArruda_autogen.dir\\ParseCache.txt"
  "CifrasClassicas-JeanArruda_autogen"
  )
endif()
