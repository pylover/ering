idf_component_register(
  INCLUDE_DIRS "include"
)


target_compile_options(${COMPONENT_LIB} INTERFACE -fms-extensions)
