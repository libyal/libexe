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
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBEXE_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYEXE = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_exeinfo.sh \
	$(TESTS_PYEXE)

check_SCRIPTS = \
	pyexe_test_file.py \
	pyexe_test_support.py \
	test_exeinfo.sh \
	test_library.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	exe_test_data_directory_descriptor \
	exe_test_debug_data \
	exe_test_error \
	exe_test_export_table \
	exe_test_file \
	exe_test_import_table \
	exe_test_io_handle \
	exe_test_notify \
	exe_test_section \
	exe_test_section_descriptor \
	exe_test_section_io_handle \
	exe_test_support

exe_test_data_directory_descriptor_SOURCES = \
	exe_test_data_directory_descriptor.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_data_directory_descriptor_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_debug_data_SOURCES = \
	exe_test_debug_data.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_debug_data_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_error_SOURCES = \
	exe_test_error.c \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_unused.h

exe_test_error_LDADD = \
	../libexe/libexe.la

exe_test_export_table_SOURCES = \
	exe_test_export_table.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_export_table_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_file_SOURCES = \
	exe_test_file.c \
	exe_test_getopt.c exe_test_getopt.h \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libcnotify.h \
	exe_test_libexe.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h

exe_test_file_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libexe/libexe.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

exe_test_import_table_SOURCES = \
	exe_test_import_table.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_import_table_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_io_handle_SOURCES = \
	exe_test_io_handle.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_io_handle_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_notify_SOURCES = \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_notify.c \
	exe_test_unused.h

exe_test_notify_LDADD = \
	../libexe/libexe.la

exe_test_section_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_section.c \
	exe_test_unused.h

exe_test_section_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_section_descriptor_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_section_descriptor.c \
	exe_test_unused.h

exe_test_section_descriptor_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_section_io_handle_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_section_io_handle.c \
	exe_test_unused.h

exe_test_section_io_handle_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_support_SOURCES = \
	exe_test_getopt.c exe_test_getopt.h \
	exe_test_libbfio.h \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libcnotify.h \
	exe_test_libexe.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_support.c

exe_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
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

