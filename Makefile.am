ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcstring \
	liberror \
	libnotify \
	libuna \
	libbfio \
	libfdata \
	libfdatetime \
	libexe \
	libsystem \
	exetools \
	po \
	manuals \
	examples \
	tests \
	macosx \
	msvscpp

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libexe.pc.in

SPEC_FILES = \
	libexe.spec \
	libexe.spec.in

EXTRA_DIST = \
	README.dll \
	README.macosx \
	README.mingw \
	README.static \
	$(GETTEXT_FILES) \
        $(PKGCONFIG_FILES) \
        $(SPEC_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libexe.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	(cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcstring && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/liberror && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libnotify && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libbfio && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdata && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdatetime && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/libexe && $(MAKE) $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS))

distclean: clean
	/bin/rm -f Makefile
	/bin/rm -f config.status
	/bin/rm -f config.cache
	/bin/rm -f config.log
	/bin/rm -f libexe.pc
	/bin/rm -f libexe.spec
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE) distclean) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

splint:
	(cd $(srcdir)/libcstring && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/liberror && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libnotify && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libbfio && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdata && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libfdatetime && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libexe && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libsystem && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/exetools && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) splint $(AM_MAKEFLAGS))

