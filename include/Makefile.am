include_HEADERS = \
	libexe.h

pkginclude_HEADERS = \
	libexe/codepage.h \
	libexe/definitions.h \
	libexe/error.h \
	libexe/extern.h \
	libexe/features.h \
	libexe/types.h

EXTRA_DIST = \
	libexe.h.in \
	libexe/definitions.h.in \
	libexe/features.h.in \
	libexe/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libexe.h
	-rm -f libexe/definitions.h
	-rm -f libexe/features.h
	-rm -f libexe/types.h
	-rm -f Makefile

