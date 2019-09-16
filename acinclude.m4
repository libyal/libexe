dnl Checks for required headers and functions
dnl
dnl Version: 20190308

  ])

dnl Function to detect if exetools dependencies are available
AC_DEFUN([AX_EXETOOLS_CHECK_LOCAL],
  [AC_CHECK_HEADERS([signal.h sys/signal.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])

  dnl Check if tools should be build as static executables
  AX_COMMON_CHECK_ENABLE_STATIC_EXECUTABLES
])

