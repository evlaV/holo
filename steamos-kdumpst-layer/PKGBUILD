# SPDX-License-Identifier: LGPL-2.1-or-later
#
# Copyright (c) 2023 Valve.
# Maintainer: Guilherme G. Piccoli <gpiccoli@igalia.com>

pkgname=steamos-kdumpst-layer
pkgver=1.0
pkgrel=2
pkgdesc="SteamOS kdumpst layer of customizations"
arch=('any')
license=('LGPL2.1')
install=skl.install
depends=('kdumpst' 'steamos-log-submitter')
conflicts=('kdump-steamos')

source=('01-steamos-custom-kdumpst.conf'
        '21-steamos-panic-sysctls.conf'
        'steamos-kdumpst-layer.service'
        'Makefile')
sha256sums=('2001a64d9ebf9432b3dd615ba0b7bfbfaa054f0e37940a7e1b6c0de6fcff5c46'
            '339525a829531f96485fb72ef2f8a3985620777111bb89b502849abea144adc7'
            '410a3d14ff8835f532289aab340c14fa98228c0a617a76ec13839d4c60e77856'
            'ac26c9f4a5fa5d72e59ce5eb09a319d1a8333673be08e0f1c5d8a85b394ef333')

package() {
	make install DESTDIR="${pkgdir}"
}
