AC_INIT([p25], [0.1], [op25-devel@yahoogroups.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])

# AC_CONFIG_HEADER(config.h)

# this macro is used to get the arguments supplied to the configure
# script (./configure --enable-debug) Check if we have enable debug
# support.
AC_MSG_CHECKING(enable debug)
debug_default="yes"
AC_ARG_ENABLE(debug, [--enable-debug=[no/yes] turn on debugging [default=$debug_default]],, enable_debug=$debug_default)
if test "x$enable_debug" = "xyes"; then
	CXXFLAGS="$CXXFLAGS -g -DDEBUG -O0"
AC_MSG_RESULT(yes)
else
	CXXFLAGS="$CXXFLAGS -O3"
AC_MSG_RESULT(no)
fi

# Checks for programs
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Require libraries
AX_BOOST_BASE([1.39])
AX_BOOST_UNIT_TEST_FRAMEWORK
AX_BOOST_PROGRAM_OPTIONS

# Compile source files in their directories (non-recursive make)
AM_INIT_AUTOMAKE([subdir-objects])

# Generate these output files
AC_CONFIG_FILES([Makefile lib/Makefile lib/p25.pc testing/Makefile src/Makefile src/brutus/Makefile src/clkdist/Makefile src/keystream/Makefile src/adp/Makefile src/cutlass/Makefile src/xfc/Makefile src/p25dump/Makefile src/pngen/Makefile src/micrypt/Makefile])

AC_OUTPUT
