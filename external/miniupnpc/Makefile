<<<<<<< HEAD
# $Id: Makefile,v 1.134 2016/10/07 09:04:36 nanard Exp $
# MiniUPnP Project
# http://miniupnp.free.fr/
# http://miniupnp.tuxfamily.org/
# https://github.com/miniupnp/miniupnp
# (c) 2005-2018 Thomas Bernard
# to install use :
# $ make DESTDIR=/tmp/dummylocation install
# or
# $ INSTALLPREFIX=/usr/local make install
# or
# $ make install (default INSTALLPREFIX is /usr)
OS = $(shell $(CC) -dumpmachine)
VERSION = $(shell cat VERSION)

ifneq (, $(findstring darwin, $(OS)))
JARSUFFIX=mac
LIBTOOL ?= $(shell which libtool)
endif
ifneq (, $(findstring linux, $(OS)))
JARSUFFIX=linux
endif
ifneq (, $(findstring mingw, $(OS))$(findstring cygwin, $(OS))$(findstring msys, $(OS)))
JARSUFFIX=win32
endif

HAVE_IPV6 ?= yes
export HAVE_IPV6

CC ?= gcc
#AR = gar
#CFLAGS = -O -g -DDEBUG
CFLAGS ?= -O
CFLAGS += -Wall
CFLAGS += -W -Wstrict-prototypes
CFLAGS += -fno-common
CFLAGS += -DMINIUPNPC_SET_SOCKET_TIMEOUT
CFLAGS += -DMINIUPNPC_GET_SRC_ADDR
CFLAGS += -D_BSD_SOURCE
CFLAGS += -D_DEFAULT_SOURCE
ifneq (, $(findstring netbsd, $(OS)))
CFLAGS += -D_NETBSD_SOURCE
endif
ifeq (, $(findstring freebsd, $(OS))$(findstring darwin, $(OS)))
#CFLAGS += -D_POSIX_C_SOURCE=200112L
CFLAGS += -D_XOPEN_SOURCE=600
endif
#CFLAGS += -ansi
#CFLAGS += -DNO_GETADDRINFO
INSTALL = install
SH = /bin/sh
JAVA = java
# see http://code.google.com/p/jnaerator/
#JNAERATOR = jnaerator-0.9.7.jar
#JNAERATOR = jnaerator-0.9.8-shaded.jar
#JNAERATORARGS = -library miniupnpc
#JNAERATOR = jnaerator-0.10-shaded.jar
#JNAERATOR = jnaerator-0.11-shaded.jar
# https://repo1.maven.org/maven2/com/nativelibs4java/jnaerator/0.12/jnaerator-0.12-shaded.jar
JNAERATOR = jnaerator-0.12-shaded.jar
JNAERATORARGS = -mode StandaloneJar -runtime JNAerator -library miniupnpc
#JNAERATORBASEURL = http://jnaerator.googlecode.com/files/
JNAERATORBASEURL = https://repo1.maven.org/maven2/com/nativelibs4java/jnaerator/0.12

ifneq (, $(findstring sun, $(OS)))
  LDLIBS=-lsocket -lnsl -lresolv
  CFLAGS += -D__EXTENSIONS__
  CFLAGS += -std=c99
endif

# APIVERSION is used to build SONAME
APIVERSION = 17

SRCS = igd_desc_parse.c miniupnpc.c minixml.c minisoap.c miniwget.c \
       upnpc.c upnpcommands.c upnpreplyparse.c testminixml.c \
       minixmlvalid.c testupnpreplyparse.c minissdpc.c \
       upnperrors.c testigddescparse.c testminiwget.c \
       connecthostport.c portlistingparse.c receivedata.c \
       upnpdev.c testportlistingparse.c miniupnpcmodule.c \
       minihttptestserver.c \
       listdevices.c

LIBOBJS = miniwget.o minixml.o igd_desc_parse.o minisoap.o \
          miniupnpc.o upnpreplyparse.o upnpcommands.o upnperrors.o \
          connecthostport.o portlistingparse.o receivedata.o upnpdev.o

ifeq (, $(findstring amiga, $(OS)))
ifeq (, $(findstring mingw, $(OS))$(findstring cygwin, $(OS))$(findstring msys, $(OS)))
CFLAGS := -fPIC $(CFLAGS)
endif
LIBOBJS := $(LIBOBJS) minissdpc.o
endif

OBJS = $(patsubst %.c,%.o,$(SRCS))

# HEADERS to install
HEADERS = miniupnpc.h miniwget.h upnpcommands.h igd_desc_parse.h \
          upnpreplyparse.h upnperrors.h miniupnpctypes.h \
          portlistingparse.h \
          upnpdev.h \
          miniupnpc_declspec.h

# library names
LIBRARY = libminiupnpc.a
ifneq (, $(findstring darwin, $(OS)))
  SHAREDLIBRARY = libminiupnpc.dylib
  SONAME = $(basename $(SHAREDLIBRARY)).$(APIVERSION).dylib
  CFLAGS := -D_DARWIN_C_SOURCE $(CFLAGS)
else
ifeq ($(JARSUFFIX), win32)
  SHAREDLIBRARY = miniupnpc.dll
else
  # Linux/BSD/etc.
  SHAREDLIBRARY = libminiupnpc.so
  SONAME = $(SHAREDLIBRARY).$(APIVERSION)
endif
endif

EXECUTABLES = upnpc-static listdevices
EXECUTABLES_ADDTESTS = testminixml minixmlvalid testupnpreplyparse \
			  testigddescparse testminiwget testportlistingparse

TESTMINIXMLOBJS = minixml.o igd_desc_parse.o testminixml.o

TESTMINIWGETOBJS = miniwget.o testminiwget.o connecthostport.o receivedata.o

TESTUPNPREPLYPARSE = testupnpreplyparse.o minixml.o upnpreplyparse.o

TESTPORTLISTINGPARSE = testportlistingparse.o minixml.o portlistingparse.o

TESTIGDDESCPARSE = testigddescparse.o igd_desc_parse.o minixml.o \
                   miniupnpc.o miniwget.o upnpcommands.o upnpreplyparse.o \
                   minisoap.o connecthostport.o receivedata.o \
                   portlistingparse.o

ifeq (, $(findstring amiga, $(OS)))
EXECUTABLES := $(EXECUTABLES) upnpc-shared
TESTMINIWGETOBJS := $(TESTMINIWGETOBJS) minissdpc.o
TESTIGDDESCPARSE := $(TESTIGDDESCPARSE) minissdpc.o
endif

LIBDIR ?= lib
# install directories
ifeq ($(strip $(PREFIX)),)
INSTALLPREFIX ?= /usr
else
INSTALLPREFIX ?= $(PREFIX)
endif
INSTALLDIRINC = $(INSTALLPREFIX)/include/miniupnpc
INSTALLDIRLIB = $(INSTALLPREFIX)/$(LIBDIR)
INSTALLDIRBIN = $(INSTALLPREFIX)/bin
INSTALLDIRMAN = $(INSTALLPREFIX)/share/man
PKGCONFIGDIR = $(INSTALLDIRLIB)/pkgconfig

FILESTOINSTALL = $(LIBRARY) $(EXECUTABLES)
ifeq (, $(findstring amiga, $(OS)))
FILESTOINSTALL := $(FILESTOINSTALL) $(SHAREDLIBRARY) miniupnpc.pc
endif


.PHONY:	install clean depend all check test everything \
	installpythonmodule updateversion
#	validateminixml validateminiwget

all:	$(LIBRARY) $(EXECUTABLES)

test:	check

check:	validateminixml validateminiwget validateupnpreplyparse \
	validateportlistingparse validateigddescparse

everything:	all $(EXECUTABLES_ADDTESTS)

pythonmodule:	$(LIBRARY) miniupnpcmodule.c setup.py
	MAKE=$(MAKE) python setup.py build
	touch $@

installpythonmodule:	pythonmodule
	MAKE=$(MAKE) python setup.py install

pythonmodule3:	$(LIBRARY) miniupnpcmodule.c setup.py
	MAKE=$(MAKE) python3 setup.py build
	touch $@

installpythonmodule3:	pythonmodule3
	MAKE=$(MAKE) python3 setup.py install

validateminixml:	minixmlvalid
	@echo "minixml validation test"
	./minixmlvalid
	touch $@

validateminiwget:	testminiwget minihttptestserver testminiwget.sh
	@echo "miniwget validation test"
	./testminiwget.sh
	touch $@

validateupnpreplyparse:	testupnpreplyparse testupnpreplyparse.sh
	@echo "upnpreplyparse validation test"
	./testupnpreplyparse.sh
	touch $@

validateportlistingparse:	testportlistingparse
	@echo "portlistingparse validation test"
	./testportlistingparse
	touch $@

validateigddescparse:	testigddescparse
	@echo "igd desc parse validation test"
	./testigddescparse testdesc/new_LiveBox_desc.xml testdesc/new_LiveBox_desc.values
	./testigddescparse testdesc/linksys_WAG200G_desc.xml testdesc/linksys_WAG200G_desc.values
	touch $@

clean:
	$(RM) $(LIBRARY) $(SHAREDLIBRARY) $(EXECUTABLES) $(OBJS) miniupnpcstrings.h
	$(RM) $(EXECUTABLES_ADDTESTS)
	# clean python stuff
	$(RM) pythonmodule pythonmodule3
	$(RM) validateminixml validateminiwget validateupnpreplyparse
	$(RM) validateigddescparse
	$(RM) minihttptestserver
	$(RM) -r build/ dist/
	#python setup.py clean
	# clean jnaerator stuff
	$(RM) _jnaerator.* java/miniupnpc_$(OS).jar

distclean: clean
	$(RM) $(JNAERATOR) java/*.jar java/*.class out.errors.txt

updateversion:	miniupnpc.h
	cp miniupnpc.h miniupnpc.h.bak
	sed 's/\(.*MINIUPNPC_API_VERSION\s\+\)[0-9]\+/\1$(APIVERSION)/' < miniupnpc.h.bak > miniupnpc.h

install:	updateversion $(FILESTOINSTALL)
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRINC)
	$(INSTALL) -m 644 $(HEADERS) $(DESTDIR)$(INSTALLDIRINC)
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRLIB)
	$(INSTALL) -m 644 $(LIBRARY) $(DESTDIR)$(INSTALLDIRLIB)
ifeq (, $(findstring amiga, $(OS)))
	$(INSTALL) -m 644 $(SHAREDLIBRARY) $(DESTDIR)$(INSTALLDIRLIB)/$(SONAME)
	ln -fs $(SONAME) $(DESTDIR)$(INSTALLDIRLIB)/$(SHAREDLIBRARY)
	$(INSTALL) -d $(DESTDIR)$(PKGCONFIGDIR)
	$(INSTALL) -m 644 miniupnpc.pc $(DESTDIR)$(PKGCONFIGDIR)
endif
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRBIN)
ifneq (, $(findstring amiga, $(OS)))
	$(INSTALL) -m 755 upnpc-static $(DESTDIR)$(INSTALLDIRBIN)/upnpc
else
	$(INSTALL) -m 755 upnpc-shared $(DESTDIR)$(INSTALLDIRBIN)/upnpc
endif
	$(INSTALL) -m 755 external-ip.sh $(DESTDIR)$(INSTALLDIRBIN)/external-ip
ifeq (, $(findstring amiga, $(OS)))
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRMAN)/man3
	$(INSTALL) -m 644 man3/miniupnpc.3 $(DESTDIR)$(INSTALLDIRMAN)/man3/miniupnpc.3
ifneq (, $(findstring linux, $(OS)))
	gzip -f $(DESTDIR)$(INSTALLDIRMAN)/man3/miniupnpc.3
endif
endif

install-static:	updateversion $(FILESTOINSTALL)
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRINC)
	$(INSTALL) -m 644 $(HEADERS) $(DESTDIR)$(INSTALLDIRINC)
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRLIB)
	$(INSTALL) -m 644 $(LIBRARY) $(DESTDIR)$(INSTALLDIRLIB)
	$(INSTALL) -d $(DESTDIR)$(INSTALLDIRBIN)
	$(INSTALL) -m 755 external-ip.sh $(DESTDIR)$(INSTALLDIRBIN)/external-ip

cleaninstall:
	$(RM) -r $(DESTDIR)$(INSTALLDIRINC)
	$(RM) $(DESTDIR)$(INSTALLDIRLIB)/$(LIBRARY)
	$(RM) $(DESTDIR)$(INSTALLDIRLIB)/$(SHAREDLIBRARY)

miniupnpc.pc:	VERSION
	$(RM) $@
	echo "prefix=$(INSTALLPREFIX)" >> $@
	echo "exec_prefix=\$${prefix}" >> $@
	echo "libdir=\$${exec_prefix}/$(LIBDIR)" >> $@
	echo "includedir=\$${prefix}/include/miniupnpc" >> $@
	echo "" >> $@
	echo "Name: miniUPnPc" >> $@
	echo "Description: UPnP IGD client lightweight library" >> $@
	echo "Version: $(VERSION)" >> $@
	echo "Libs: -L\$${libdir} -lminiupnpc" >> $@
	echo "Cflags: -I\$${includedir}" >> $@

depend:
	makedepend -Y -- $(CFLAGS) -- $(SRCS) 2>/dev/null

$(LIBRARY):	$(LIBOBJS)
ifneq (, $(findstring darwin, $(OS)))
	$(LIBTOOL) -static -o $@ $?
else
	$(AR) crs $@ $?
endif

$(SHAREDLIBRARY):	$(LIBOBJS)
ifneq (, $(findstring darwin, $(OS)))
#	$(CC) -dynamiclib $(LDFLAGS) -Wl,-install_name,$(SONAME) -o $@ $^
	$(CC) -dynamiclib $(LDFLAGS) -Wl,-install_name,$(INSTALLDIRLIB)/$(SONAME) -o $@ $^
else
	$(CC) -shared $(LDFLAGS) -Wl,-soname,$(SONAME) -o $@ $^
endif

upnpc-static:	upnpc.o $(LIBRARY)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

upnpc-shared:	upnpc.o $(SHAREDLIBRARY)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

listdevices:	listdevices.o $(LIBRARY)

testminixml:	$(TESTMINIXMLOBJS)

testminiwget:	$(TESTMINIWGETOBJS)

minixmlvalid:	minixml.o minixmlvalid.o

testupnpreplyparse:	$(TESTUPNPREPLYPARSE)

testigddescparse:	$(TESTIGDDESCPARSE)

testportlistingparse:	$(TESTPORTLISTINGPARSE)

miniupnpcstrings.h:	miniupnpcstrings.h.in updateminiupnpcstrings.sh VERSION
	$(SH) updateminiupnpcstrings.sh

# ftp tool supplied with OpenBSD can download files from http.
jnaerator-%.jar:
	wget $(JNAERATORBASEURL)/$@ || \
	curl -o $@ $(JNAERATORBASEURL)/$@ || \
	ftp $(JNAERATORBASEURL)/$@

jar: $(SHAREDLIBRARY)  $(JNAERATOR)
	$(JAVA) -jar $(JNAERATOR) $(JNAERATORARGS) \
	miniupnpc.h miniupnpc_declspec.h upnpcommands.h upnpreplyparse.h \
	igd_desc_parse.h miniwget.h upnperrors.h $(SHAREDLIBRARY) \
	-package fr.free.miniupnp -o . -jar java/miniupnpc_$(JARSUFFIX).jar -v

mvn_install:
	mvn install:install-file -Dfile=java/miniupnpc_$(JARSUFFIX).jar \
	 -DgroupId=com.github \
	 -DartifactId=miniupnp \
	 -Dversion=$(VERSION) \
	 -Dpackaging=jar \
	 -Dclassifier=$(JARSUFFIX) \
	 -DgeneratePom=true \
	 -DcreateChecksum=true

# make .deb packages
deb: /usr/share/pyshared/stdeb all
	(python setup.py --command-packages=stdeb.command bdist_deb)

# install .deb packages
ideb:
	(sudo dpkg -i deb_dist/*.deb)

/usr/share/pyshared/stdeb: /usr/share/doc/python-all-dev
	(sudo apt-get install python-stdeb)

/usr/share/doc/python-all-dev:
	(sudo apt-get install python-all-dev)

minihttptestserver:	minihttptestserver.o

# DO NOT DELETE THIS LINE -- make depend depends on it.

igd_desc_parse.o: igd_desc_parse.h
miniupnpc.o: miniupnpc.h miniupnpc_declspec.h igd_desc_parse.h upnpdev.h
miniupnpc.o: minissdpc.h miniwget.h minisoap.h minixml.h upnpcommands.h
miniupnpc.o: upnpreplyparse.h portlistingparse.h miniupnpctypes.h
miniupnpc.o: connecthostport.h
minixml.o: minixml.h
minisoap.o: minisoap.h miniupnpcstrings.h
miniwget.o: miniupnpcstrings.h miniwget.h miniupnpc_declspec.h
miniwget.o: connecthostport.h receivedata.h
upnpc.o: miniwget.h miniupnpc_declspec.h miniupnpc.h igd_desc_parse.h
upnpc.o: upnpdev.h upnpcommands.h upnpreplyparse.h portlistingparse.h
upnpc.o: miniupnpctypes.h upnperrors.h miniupnpcstrings.h
upnpcommands.o: upnpcommands.h upnpreplyparse.h portlistingparse.h
upnpcommands.o: miniupnpc_declspec.h miniupnpctypes.h miniupnpc.h
upnpcommands.o: igd_desc_parse.h upnpdev.h
upnpreplyparse.o: upnpreplyparse.h minixml.h
testminixml.o: minixml.h igd_desc_parse.h
minixmlvalid.o: minixml.h
testupnpreplyparse.o: upnpreplyparse.h
minissdpc.o: minissdpc.h miniupnpc_declspec.h upnpdev.h miniupnpc.h
minissdpc.o: igd_desc_parse.h receivedata.h codelength.h
upnperrors.o: upnperrors.h miniupnpc_declspec.h upnpcommands.h
upnperrors.o: upnpreplyparse.h portlistingparse.h miniupnpctypes.h
upnperrors.o: miniupnpc.h igd_desc_parse.h upnpdev.h
testigddescparse.o: igd_desc_parse.h minixml.h miniupnpc.h
testigddescparse.o: miniupnpc_declspec.h upnpdev.h
testminiwget.o: miniwget.h miniupnpc_declspec.h
connecthostport.o: connecthostport.h
portlistingparse.o: portlistingparse.h miniupnpc_declspec.h miniupnpctypes.h
portlistingparse.o: minixml.h
receivedata.o: receivedata.h
upnpdev.o: upnpdev.h miniupnpc_declspec.h
testportlistingparse.o: portlistingparse.h miniupnpc_declspec.h
testportlistingparse.o: miniupnpctypes.h
miniupnpcmodule.o: miniupnpc.h miniupnpc_declspec.h igd_desc_parse.h
miniupnpcmodule.o: upnpdev.h upnpcommands.h upnpreplyparse.h
miniupnpcmodule.o: portlistingparse.h miniupnpctypes.h upnperrors.h
listdevices.o: miniupnpc.h miniupnpc_declspec.h igd_desc_parse.h upnpdev.h
=======
# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rocksteady/TRTL3/turtle-tacos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rocksteady/TRTL3/turtle-tacos

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	cd /home/rocksteady/TRTL3/turtle-tacos && $(CMAKE_COMMAND) -E cmake_progress_start /home/rocksteady/TRTL3/turtle-tacos/CMakeFiles /home/rocksteady/TRTL3/turtle-tacos/external/miniupnpc/CMakeFiles/progress.marks
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f CMakeFiles/Makefile2 external/miniupnpc/all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rocksteady/TRTL3/turtle-tacos/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f CMakeFiles/Makefile2 external/miniupnpc/clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f CMakeFiles/Makefile2 external/miniupnpc/preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f CMakeFiles/Makefile2 external/miniupnpc/preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

# Convenience name for target.
external/miniupnpc/CMakeFiles/upnpc-static.dir/rule:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f CMakeFiles/Makefile2 external/miniupnpc/CMakeFiles/upnpc-static.dir/rule
.PHONY : external/miniupnpc/CMakeFiles/upnpc-static.dir/rule

# Convenience name for target.
upnpc-static: external/miniupnpc/CMakeFiles/upnpc-static.dir/rule

.PHONY : upnpc-static

# fast build rule for target.
upnpc-static/fast:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/build
.PHONY : upnpc-static/fast

connecthostport.o: connecthostport.c.o

.PHONY : connecthostport.o

# target to build an object file
connecthostport.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/connecthostport.c.o
.PHONY : connecthostport.c.o

connecthostport.i: connecthostport.c.i

.PHONY : connecthostport.i

# target to preprocess a source file
connecthostport.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/connecthostport.c.i
.PHONY : connecthostport.c.i

connecthostport.s: connecthostport.c.s

.PHONY : connecthostport.s

# target to generate assembly for a file
connecthostport.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/connecthostport.c.s
.PHONY : connecthostport.c.s

igd_desc_parse.o: igd_desc_parse.c.o

.PHONY : igd_desc_parse.o

# target to build an object file
igd_desc_parse.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/igd_desc_parse.c.o
.PHONY : igd_desc_parse.c.o

igd_desc_parse.i: igd_desc_parse.c.i

.PHONY : igd_desc_parse.i

# target to preprocess a source file
igd_desc_parse.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/igd_desc_parse.c.i
.PHONY : igd_desc_parse.c.i

igd_desc_parse.s: igd_desc_parse.c.s

.PHONY : igd_desc_parse.s

# target to generate assembly for a file
igd_desc_parse.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/igd_desc_parse.c.s
.PHONY : igd_desc_parse.c.s

minisoap.o: minisoap.c.o

.PHONY : minisoap.o

# target to build an object file
minisoap.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minisoap.c.o
.PHONY : minisoap.c.o

minisoap.i: minisoap.c.i

.PHONY : minisoap.i

# target to preprocess a source file
minisoap.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minisoap.c.i
.PHONY : minisoap.c.i

minisoap.s: minisoap.c.s

.PHONY : minisoap.s

# target to generate assembly for a file
minisoap.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minisoap.c.s
.PHONY : minisoap.c.s

minissdpc.o: minissdpc.c.o

.PHONY : minissdpc.o

# target to build an object file
minissdpc.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minissdpc.c.o
.PHONY : minissdpc.c.o

minissdpc.i: minissdpc.c.i

.PHONY : minissdpc.i

# target to preprocess a source file
minissdpc.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minissdpc.c.i
.PHONY : minissdpc.c.i

minissdpc.s: minissdpc.c.s

.PHONY : minissdpc.s

# target to generate assembly for a file
minissdpc.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minissdpc.c.s
.PHONY : minissdpc.c.s

miniupnpc.o: miniupnpc.c.o

.PHONY : miniupnpc.o

# target to build an object file
miniupnpc.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniupnpc.c.o
.PHONY : miniupnpc.c.o

miniupnpc.i: miniupnpc.c.i

.PHONY : miniupnpc.i

# target to preprocess a source file
miniupnpc.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniupnpc.c.i
.PHONY : miniupnpc.c.i

miniupnpc.s: miniupnpc.c.s

.PHONY : miniupnpc.s

# target to generate assembly for a file
miniupnpc.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniupnpc.c.s
.PHONY : miniupnpc.c.s

miniwget.o: miniwget.c.o

.PHONY : miniwget.o

# target to build an object file
miniwget.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniwget.c.o
.PHONY : miniwget.c.o

miniwget.i: miniwget.c.i

.PHONY : miniwget.i

# target to preprocess a source file
miniwget.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniwget.c.i
.PHONY : miniwget.c.i

miniwget.s: miniwget.c.s

.PHONY : miniwget.s

# target to generate assembly for a file
miniwget.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/miniwget.c.s
.PHONY : miniwget.c.s

minixml.o: minixml.c.o

.PHONY : minixml.o

# target to build an object file
minixml.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minixml.c.o
.PHONY : minixml.c.o

minixml.i: minixml.c.i

.PHONY : minixml.i

# target to preprocess a source file
minixml.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minixml.c.i
.PHONY : minixml.c.i

minixml.s: minixml.c.s

.PHONY : minixml.s

# target to generate assembly for a file
minixml.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/minixml.c.s
.PHONY : minixml.c.s

portlistingparse.o: portlistingparse.c.o

.PHONY : portlistingparse.o

# target to build an object file
portlistingparse.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/portlistingparse.c.o
.PHONY : portlistingparse.c.o

portlistingparse.i: portlistingparse.c.i

.PHONY : portlistingparse.i

# target to preprocess a source file
portlistingparse.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/portlistingparse.c.i
.PHONY : portlistingparse.c.i

portlistingparse.s: portlistingparse.c.s

.PHONY : portlistingparse.s

# target to generate assembly for a file
portlistingparse.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/portlistingparse.c.s
.PHONY : portlistingparse.c.s

receivedata.o: receivedata.c.o

.PHONY : receivedata.o

# target to build an object file
receivedata.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/receivedata.c.o
.PHONY : receivedata.c.o

receivedata.i: receivedata.c.i

.PHONY : receivedata.i

# target to preprocess a source file
receivedata.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/receivedata.c.i
.PHONY : receivedata.c.i

receivedata.s: receivedata.c.s

.PHONY : receivedata.s

# target to generate assembly for a file
receivedata.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/receivedata.c.s
.PHONY : receivedata.c.s

upnpc.o: upnpc.c.o

.PHONY : upnpc.o

# target to build an object file
upnpc.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpc.c.o
.PHONY : upnpc.c.o

upnpc.i: upnpc.c.i

.PHONY : upnpc.i

# target to preprocess a source file
upnpc.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpc.c.i
.PHONY : upnpc.c.i

upnpc.s: upnpc.c.s

.PHONY : upnpc.s

# target to generate assembly for a file
upnpc.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpc.c.s
.PHONY : upnpc.c.s

upnpcommands.o: upnpcommands.c.o

.PHONY : upnpcommands.o

# target to build an object file
upnpcommands.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpcommands.c.o
.PHONY : upnpcommands.c.o

upnpcommands.i: upnpcommands.c.i

.PHONY : upnpcommands.i

# target to preprocess a source file
upnpcommands.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpcommands.c.i
.PHONY : upnpcommands.c.i

upnpcommands.s: upnpcommands.c.s

.PHONY : upnpcommands.s

# target to generate assembly for a file
upnpcommands.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpcommands.c.s
.PHONY : upnpcommands.c.s

upnperrors.o: upnperrors.c.o

.PHONY : upnperrors.o

# target to build an object file
upnperrors.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnperrors.c.o
.PHONY : upnperrors.c.o

upnperrors.i: upnperrors.c.i

.PHONY : upnperrors.i

# target to preprocess a source file
upnperrors.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnperrors.c.i
.PHONY : upnperrors.c.i

upnperrors.s: upnperrors.c.s

.PHONY : upnperrors.s

# target to generate assembly for a file
upnperrors.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnperrors.c.s
.PHONY : upnperrors.c.s

upnpreplyparse.o: upnpreplyparse.c.o

.PHONY : upnpreplyparse.o

# target to build an object file
upnpreplyparse.c.o:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpreplyparse.c.o
.PHONY : upnpreplyparse.c.o

upnpreplyparse.i: upnpreplyparse.c.i

.PHONY : upnpreplyparse.i

# target to preprocess a source file
upnpreplyparse.c.i:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpreplyparse.c.i
.PHONY : upnpreplyparse.c.i

upnpreplyparse.s: upnpreplyparse.c.s

.PHONY : upnpreplyparse.s

# target to generate assembly for a file
upnpreplyparse.c.s:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(MAKE) -f external/miniupnpc/CMakeFiles/upnpc-static.dir/build.make external/miniupnpc/CMakeFiles/upnpc-static.dir/upnpreplyparse.c.s
.PHONY : upnpreplyparse.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... test"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... upnpc-static"
	@echo "... connecthostport.o"
	@echo "... connecthostport.i"
	@echo "... connecthostport.s"
	@echo "... igd_desc_parse.o"
	@echo "... igd_desc_parse.i"
	@echo "... igd_desc_parse.s"
	@echo "... minisoap.o"
	@echo "... minisoap.i"
	@echo "... minisoap.s"
	@echo "... minissdpc.o"
	@echo "... minissdpc.i"
	@echo "... minissdpc.s"
	@echo "... miniupnpc.o"
	@echo "... miniupnpc.i"
	@echo "... miniupnpc.s"
	@echo "... miniwget.o"
	@echo "... miniwget.i"
	@echo "... miniwget.s"
	@echo "... minixml.o"
	@echo "... minixml.i"
	@echo "... minixml.s"
	@echo "... portlistingparse.o"
	@echo "... portlistingparse.i"
	@echo "... portlistingparse.s"
	@echo "... receivedata.o"
	@echo "... receivedata.i"
	@echo "... receivedata.s"
	@echo "... upnpc.o"
	@echo "... upnpc.i"
	@echo "... upnpc.s"
	@echo "... upnpcommands.o"
	@echo "... upnpcommands.i"
	@echo "... upnpcommands.s"
	@echo "... upnperrors.o"
	@echo "... upnperrors.i"
	@echo "... upnperrors.s"
	@echo "... upnpreplyparse.o"
	@echo "... upnpreplyparse.i"
	@echo "... upnpreplyparse.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	cd /home/rocksteady/TRTL3/turtle-tacos && $(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

>>>>>>> blood in blood out
