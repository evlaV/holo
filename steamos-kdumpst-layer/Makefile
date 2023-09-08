# SPDX-License-Identifier: LGPL-2.1-or-later
#
# Copyright (c) 2023 Valve.
# Maintainer: Guilherme G. Piccoli <gpiccoli@igalia.com>

prefix     := /usr
libdir     := $(prefix)/lib
sharedir     := $(prefix)/share

systemdunitsdir := $(shell pkg-config --define-variable=prefix=$(prefix) --variable=systemdsystemunitdir systemd 2>/dev/null \
                          || echo $(libdir)/systemd/system/)
sysctldir := $(shell pkg-config --define-variable=prefix=$(prefix) --variable=sysctldir systemd 2>/dev/null \
                          || echo $(libdir)/sysctl.d/)
all:

install: all
	install -D -m0644 01-steamos-custom-kdumpst.conf $(DESTDIR)$(sharedir)/kdumpst.d/01-steamos-custom-kdumpst.conf
	install -D -m0644 21-steamos-panic-sysctls.conf  $(DESTDIR)$(sysctldir)/21-steamos-panic-sysctls.conf
	install -D -m0644 steamos-kdumpst-layer.service $(DESTDIR)$(systemdunitsdir)/steamos-kdumpst-layer.service
