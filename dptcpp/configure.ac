#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
LT_PREREQ([2.4])
AC_INIT(dptcpp, 0.1, denes.almasi@gmail.com)
LT_INIT
AM_INIT_AUTOMAKE(dptcpp, 0.1)
LT_LANG([C++])
#PKG_PROG_PKG_VERSION([0.25])
AC_PREFIX_DEFAULT([/usr])
AC_CONFIG_SRCDIR([src/Exception.cpp])
AC_CONFIG_HEADERS([config.h])
# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
BOOST_REQUIRE
BOOST_ASIO
BOOST_FUNCTION
BOOST_TOKENIZER
BOOST_SIGNALS
BOOST_THREADS
BOOST_SYSTEM
PKG_CHECK_MODULES([DPTCPP], [glibmm-2.4 >= 2.30, libxml++-2.6 >= 2.34])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile inc/Makefile])
AC_OUTPUT
