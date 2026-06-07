AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

check_PYTHONdir = $(abs_top_builddir)

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_PYTHON_SCRIPTS = \
	pyexe_test_file.py \
	pyexe_test_support.py

check_PROGRAMS = \
	exe_test_coff_header \
	exe_test_coff_optional_header \
	exe_test_data_directory_descriptor \
	exe_test_debug_data \
	exe_test_error \
	exe_test_export_table \
	exe_test_file \
	exe_test_import_table \
	exe_test_io_handle \
	exe_test_le_header \
	exe_test_mz_header \
	exe_test_ne_header \
	exe_test_notify \
	exe_test_section \
	exe_test_section_descriptor \
	exe_test_section_io_handle \
	exe_test_support \
	exe_test_tools_info_handle \
	exe_test_tools_output \
	exe_test_tools_signal

exe_test_coff_header_SOURCES = \
	exe_test_coff_header.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_coff_header_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_coff_optional_header_SOURCES = \
	exe_test_coff_optional_header.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_coff_optional_header_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

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
	exe_test_functions.c exe_test_functions.h \
	exe_test_getopt.c exe_test_getopt.h \
	exe_test_libbfio.h \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libcnotify.h \
	exe_test_libexe.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
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

exe_test_le_header_SOURCES = \
	exe_test_le_header.c \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_unused.h

exe_test_le_header_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_mz_header_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_mz_header.c \
	exe_test_unused.h

exe_test_mz_header_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_ne_header_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_ne_header.c \
	exe_test_unused.h

exe_test_ne_header_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_notify_SOURCES = \
	exe_test_libcerror.h \
	exe_test_libexe.h \
	exe_test_macros.h \
	exe_test_notify.c \
	exe_test_unused.h

exe_test_notify_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

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
	exe_test_functions.c exe_test_functions.h \
	exe_test_getopt.c exe_test_getopt.h \
	exe_test_libbfio.h \
	exe_test_libcerror.h \
	exe_test_libclocale.h \
	exe_test_libcnotify.h \
	exe_test_libexe.h \
	exe_test_libuna.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_support.c \
	exe_test_unused.h

exe_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_tools_info_handle_SOURCES = \
	../exetools/info_handle.c ../exetools/info_handle.h \
	exe_test_libcerror.h \
	exe_test_macros.h \
	exe_test_memory.c exe_test_memory.h \
	exe_test_tools_info_handle.c \
	exe_test_unused.h

exe_test_tools_info_handle_LDADD = \
	@LIBCLOCALE_LIBADD@ \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

exe_test_tools_output_SOURCES = \
	../exetools/exetools_output.c ../exetools/exetools_output.h \
	exe_test_libcerror.h \
	exe_test_macros.h \
	exe_test_tools_output.c \
	exe_test_unused.h

exe_test_tools_output_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

exe_test_tools_signal_SOURCES = \
	../exetools/exetools_signal.c ../exetools/exetools_signal.h \
	exe_test_libcerror.h \
	exe_test_macros.h \
	exe_test_tools_signal.c \
	exe_test_unused.h

exe_test_tools_signal_LDADD = \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libexe.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libexe

test_inputs_pyexe.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyexe

test_inputs_exeinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) exeinfo

test_library: package.m4 test_inputs_libexe.at test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

test_python_module: package.m4 test_inputs_pyexe.at test_macros.at test_python_module.at

test_tools: package.m4 test_inputs_exeinfo.at test_macros.at test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_PYTHON_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in \
	notify_stream.log

