# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Compilador_aula_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Compilador_aula_autogen.dir\\ParseCache.txt"
  "Compilador_aula_autogen"
  )
endif()
