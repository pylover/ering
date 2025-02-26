set(sources
  "ering.c"
)


idf_component_register(
  SRCS "${sources}"
  INCLUDE_DIRS "include"
)


target_compile_options(${COMPONENT_LIB} PRIVATE -fms-extensions)
