install(
    TARGETS brawl_masters_exe
    RUNTIME COMPONENT brawl_masters_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
