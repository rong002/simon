set(simonrecognitionresult_LIB_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/recognitionresult.cpp
)

set(simonrecognitionresult_LIB_HDRS
  simonrecognitionresult_export.h
  recognitionresult.h
)

kde4_add_library(simonrecognitionresult SHARED ${simonrecognitionresult_LIB_SRCS})
target_link_libraries(simonrecognitionresult ${QT_LIBRARIES} ${KDE4_KDECORE_LIBS})

set_target_properties(simonrecognitionresult
  PROPERTIES VERSION ${CMAKE_SIMON_VERSION_STRING} SOVERSION ${CMAKE_SIMON_VERSION_MAJOR}
)

install(FILES ${simonrecognitionresult_LIB_HDRS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/simon/simonrecognitionresult
  COMPONENT simondevel
)

install(TARGETS simonrecognitionresult DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simoncore )
