AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBEXE_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYEXE = \
	test_python_functions.sh \
	test_pyexe_set_ascii_codepage.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_exeinfo.sh \
	$(TESTS_PYEXE)

check_SCRIPTS = \
	pyexe_test_get_version.py \
	pyexe_test_open_close.py \
	pyexe_test_read.py \
	pyexe_test_seek.py \
	pyexe_test_set_ascii_codepage.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_exeinfo.sh \
	test_python_functions.sh \
	test_pyexe_set_ascii_codepage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	exe_test_error \
	exe_test_file \
	exe_test_notify \
	exe_test_open_close \
	exe_test_read \
	exe_test_section \
	exe_test_seek \
	exe_test_support

exe_test_error_SOURCES = \
	exe_test_error.c \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_unused.h

exe_test_error_LDADD = \
	../libexe/libexe.la

exe_test_file_SOURCES = \
	exe_test_file.c \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libexe.h \
	exe_test_libcsystem.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h

exe_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_notify_SOURCES = \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_notify.c \
	exe_test_unused.h

exe_test_notify_LDADD = \
	../libexe/libexe.la

exe_test_open_close_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_libexe.h \
	exe_test_open_close.c \
	exe_test_unused.h

exe_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

exe_test_read_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_libexe.h \
	exe_test_read.c \
	exe_test_unused.h

exe_test_read_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

exe_test_section_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_section.c \
	exe_test_unused.h

exe_test_section_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

exe_test_seek_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_libexe.h \
	exe_test_seek.c \
	exe_test_unused.h

exe_test_seek_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

exe_test_support_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libexe.h \
	exe_test_libcsystem.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_support.c

exe_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

