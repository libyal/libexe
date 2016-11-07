# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

am_pyexe_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pyexe.c pyexe.h \
	pyexe_codepage.c pyexe_codepage.h \
	pyexe_error.c pyexe_error.h \
	pyexe_datetime.c pyexe_datetime.h \
	pyexe_file.c pyexe_file.h \
	pyexe_file_object_io_handle.c pyexe_file_object_io_handle.h \
	pyexe_integer.c pyexe_integer.h \
	pyexe_libbfio.h \
	pyexe_libcerror.h \
	pyexe_libclocale.h \
	pyexe_libexe.h \
	pyexe_section.c pyexe_section.h \
	pyexe_sections.c pyexe_sections.h \
	pyexe_python.h \
	pyexe_unused.h

pyexec_LTLIBRARIES = pyexe.la

nodist_pyexe_la_SOURCES = $(BUILT_SOURCES)

pyexe_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libexe/libexe.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyexe_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyexe_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyexe/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyexe*.[ch]

distclean: clean
	/bin/rm -f Makefile

