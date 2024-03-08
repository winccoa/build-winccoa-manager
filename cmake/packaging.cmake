include(${CMAKE_CURRENT_LIST_DIR}/general.cmake)

if (WIN32)
  set(CPACK_GENERATOR "ZIP")
elseif(DEBIAN)
  set(CPACK_GENERATOR "DEB")
elseif(REDHAT)
  set(CPACK_GENERATOR "RPM")
endif()

if (WIN32)
  set(CPACK_PACKAGING_INSTALL_PREFIX "")
else()
  # Set the install prefix to the WinCC_OA installation directory
  set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/WinCC_OA/${WCCOA_VERSION_MAJOR}.${WCCOA_VERSION_MINOR}/")
endif()

if (NOT ${WCCOA_VERSION_MAJOR})
  message(FATAL_ERROR "WCCOA_VERSION_MAJOR is not set, make sure API_ROOT is set correctly!")
endif()

# Set the package dependencies
set(CPACK_DEBIAN_PACKAGE_DEPENDS "winccoa-${WCCOA_VERSION_MAJOR}.${WCCOA_VERSION_MINOR}-base")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_RPM_PACKAGE_REQUIRES "winccoa-${WCCOA_VERSION_MAJOR}.${WCCOA_VERSION_MINOR}-Base")
set(CPACK_RPM_PACKAGE_AUTOREQ ON)

set(CPACK_STRIP_FILES ON)

if (NOT CPACK_PACKAGE_CONTACT)
  message(WARNING "CPACK_PACKAGE_CONTACT is not set, using default value")
  set(CPACK_PACKAGE_CONTACT "undefined")
endif()

include(CPack)
