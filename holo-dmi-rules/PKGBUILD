# Maintainer: John Schoenick <johns@valvesoftware.com>

#  SPDX-License-Identifier: LGPL-2.1+
#
#  This file is part of the Holo project.
#
#  Holo is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License as
#  published by the Free Software Foundation; either version 2.1 of the License,
#  or (at your option) any later version.

pkgname='holo-dmi-rules'
pkgver=1.1
pkgrel=1
pkgdesc="Holo tmpfiles.d rules for accessing DMI info"
arch=('any')
license=('LGPL2.1')
depends=()
source=('dmi-product-serial.conf')
sha256sums=('5896b4569a2cc1354b6e9316b2a35899b315d2f710420f1ca6e68c2d1db0f054')

package() {
  # Loosen the product_serial node to 440 / root:wheel, rather than 400 / root:root to allow the physical users to read
  # S/N without auth.
  install -D -m644 "$srcdir"/dmi-product-serial.conf "$pkgdir"/usr/lib/tmpfiles.d/dmi-product-serial.conf
}
