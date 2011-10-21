AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libexe.la

libexe_la_SOURCES = \
	libexe.c \
	libexe_array_type.c libexe_array_type.h \
	libexe_codepage.h \
	libexe_debug.c libexe_debug.h \
	libexe_definitions.h \
	libexe_error.c libexe_error.h \
	libexe_extern.h \
	libexe_file.c libexe_file.h \
	libexe_io_handle.c libexe_io_handle.h \
	libexe_libbfio.h \
	libexe_libfdata.h \
	libexe_libdatetime.h \
	libexe_libuna.h \
	libexe_notify.c libexe_notify.h \
	libexe_section.c libexe_section.h \
	libexe_section_descriptor.c libexe_section_descriptor.h \
	libexe_support.c libexe_support.h \
	libexe_types.h \
	libexe_unused.h \
	exe_file_header.h \
	exe_section_table.h

libexe_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libnotify/libnotify.la \
	@LIBUNA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@

libexe_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libexe_definitions.h.in \
	libexe.rc \
	libexe.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libexe_definitions.h
	/bin/rm -f libexe.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libexe ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libexe_la_SOURCES) 

