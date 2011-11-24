AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libsystem \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@ \
	@LIBEXE_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	exeinfo

exeinfo_SOURCES = \
	exeinfo.c \
	exeinput.c exeinput.h \
	exeoutput.c exeoutput.h \
	exetools_libfdatetime.h \
	exetools_libexe.h \
	exetools_libuna.h \
	info_handle.c info_handle.h

exeinfo_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libexe/libexe.la \
	../libsystem/libsystem.la \
	@LIBUNA_LIBADD@ \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on exeinfo ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(exeinfo_SOURCES) 

