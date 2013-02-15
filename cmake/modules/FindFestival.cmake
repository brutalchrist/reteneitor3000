#FIND_PATH(FESTIVAL_INCLUDE_DIR foo.h /usr/include/foo /usr/local/include/foo)

FIND_FILE(FESTIVAL_LIBRARY NAMES festival PATH /usr/bin) 

IF (FESTIVAL_LIBRARY)
   SET(FESTIVAL_FOUND TRUE)
ENDIF (FESTIVAL_LIBRARY)


IF (FESTIVAL_FOUND)
   IF (NOT FESTIVAL_FIND_QUIETLY)
	    MESSAGE(STATUS "Found FESTIVAL: ${FESTIVAL_LIBRARY}")
   ENDIF (NOT FESTIVAL_FIND_QUIETLY)
ELSE (FESTIVAL_FOUND)
   IF (Festival_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find FESTIVAL, instalar festival festvox-ellpc11k")
   ENDIF (Festival_FIND_REQUIRED)
ENDIF (FESTIVAL_FOUND)
