#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([pagwin_spellcheck], [0.1], [bugs@pagwin.xyz])
AM_INIT_AUTOMAKE([-Wall foreign])
#AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(aspell,new_aspell_config)
# Checks for header files.
AC_CHECK_HEADER(stdio.h, [], [AC_MSG_ERROR([stdio.h functionality is needed by spellntnt.])])
AC_CHECK_HEADER(aspell.h, [],[AC_MSG_ERROR([Please install aspell header file before configuring.])])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
