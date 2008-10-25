include(FindQt4)
find_package(KDE4 REQUIRED)
include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include(KDE4Defaults)

set (QT_USE_QTMAIN true)

if(UNIX)
	FIND_LIBRARY(X11_XTest_LIB Xtst ${X11_LIB_SEARCH_PATH})
endif(UNIX)
 
set( eventsimulation_LIB_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/eventhandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/coreevents.cpp
)


set ( eventsimulation_LIB_LINUX_SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/xevents.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xeventsprivate.cpp
	)

set ( eventsimulation_LIB_WINDOWS_SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/windowsevents.cpp
	)

set( eventsimulation_LIB_HDRS
  eventsimulation_export.h
  eventhandler.h
)


IF(UNIX)
	kde4_add_library( eventsimulation  SHARED ${eventsimulation_LIB_SRCS} ${eventsimulation_LIB_LINUX_SRCS} )
	target_link_libraries( eventsimulation ${QT_LIBRARIES} ${KDE4_KDEUI_LIBS} ${X11_XTest_LIB} )
ENDIF(UNIX)

IF(WIN32)
	kde4_add_library( eventsimulation  SHARED ${eventsimulation_LIB_SRCS} ${eventsimulation_LIB_WINDOWS_SRCS} )
	target_link_libraries( eventsimulation ${QT_LIBRARIES} ${KDE4_KDECORE_LIBS} )
ENDIF(WIN32)


set_target_properties( eventsimulation
  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
)

install( FILES ${eventsimulation_LIB_HDRS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/simon/eventhandler
  COMPONENT Devel
)
 
install( TARGETS eventsimulation  ${INSTALL_TARGETS_DEFAULT_ARGS} )