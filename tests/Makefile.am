AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	test_pyexe_set_ascii_codepage.sh \
	test_pyexe_open_close.sh \
	test_pyexe_read.sh \
	test_pyexe_seek.sh
endif

TESTS = \
	test_set_ascii_codepage.sh \
	test_open_close.sh \
	test_read.sh \
	test_seek.sh \
	test_exeinfo.sh \
	$(TESTS_PYEXE)

check_SCRIPTS = \
	pyexe_test_open_close.py \
	pyexe_test_read.py \
	pyexe_test_seek.py \
	pyexe_test_set_ascii_codepage.py \
	test_exeinfo.sh \
	test_open_close.sh \
	test_pyexe_open_close.sh \
	test_pyexe_read.sh \
	test_pyexe_seek.sh \
	test_pyexe_set_ascii_codepage.sh \
	test_read.sh \
	test_runner.sh \
	test_seek.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	exe_test_open_close \
	exe_test_read \
	exe_test_seek \
	exe_test_set_ascii_codepage

exe_test_open_close_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_libcstring.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_open_close.c \
	exe_test_unused.h

exe_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

exe_test_read_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_libcstring.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_read.c \
	exe_test_unused.h

exe_test_read_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

exe_test_seek_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_libcstring.h \
	exe_test_libcsystem.h \
	exe_test_libcthreads.h \
	exe_test_seek.c \
	exe_test_unused.h

exe_test_seek_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

exe_test_set_ascii_codepage_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libexe.h \
	exe_test_libcstring.h \
	exe_test_set_ascii_codepage.c

exe_test_set_ascii_codepage_LDADD = \
	../libexe/libexe.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

