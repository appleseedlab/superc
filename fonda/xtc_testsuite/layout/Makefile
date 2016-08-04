#
# xtc - The eXTensible Compiler
# Copyright (C) 2007-2012 Robert Grimm
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.
#

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makebase
endif

.PHONY : test

setup :
	$(CC) $(CFLAGS) -o headergen headergen.c
	./headergen > metadata.h
	$(CPP) $(CPPFLAGS) test.c > test.E

run-java :
	$(JAVA) xtc.lang.C -analyze test.E

cleanall :
	$(RM) headergen metadata.h test.E

test : setup run-java cleanall
