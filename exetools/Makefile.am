AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
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
	@LIBEXE_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	exeinfo

exeinfo_SOURCES = \
	exeinfo.c \
	exetools_getopt.c exetools_getopt.h \
	exetools_i18n.h \
	exetools_libbfio.h \
	exetools_libcerror.h \
	exetools_libclocale.h \
	exetools_libcnotify.h \
	exetools_libfdatetime.h \
	exetools_libexe.h \
	exetools_libuna.h \
	exetools_output.c exetools_output.h \
	exetools_signal.c exetools_signal.h \
	exetools_unused.h \
	info_handle.c info_handle.h

exeinfo_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libexe/libexe.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on exeinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(exeinfo_SOURCES)

