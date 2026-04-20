# SPDX-License-Identifier: LGPL-2.1-or-later
#
# Copyright (c) 2023 Valve.
# Maintainer: Guilherme G. Piccoli <gpiccoli@igalia.com>

pkgname=steamos-kdumpst-layer
pkgver=1.1
pkgrel=1
pkgdesc="SteamOS kdumpst layer of customizations"
arch=('any')
license=('LGPL2.1')
install=hkl.install
depends=('kdumpst' 'steamos-log-submitter')
conflicts=('kdump-steamos')

source=('01-holo-custom-kdumpst.conf'
        '21-holo-panic-sysctls.conf'
        'holo-kdumpst-layer.service'
        'Makefile')
sha256sums=('a79db29dc9fc70ba660f2f738647066e3d631cb2a042fa1e0fb37efbc204ba55'
            '37df615deeb0ab3c486c881dd0610fc4fb239e66efe1180fb20800f46b9563fc'
            '70ce58216b8745428bcc278e1a3834410ee76f0f9ed8fa1e9fb9f32892a78913'
            '8dc9d591e3e083ee4f22a14eb3cdd19eecd00d49a87e751780d5ed7db2c67f58')

package() {
	make install DESTDIR="${pkgdir}"
}
