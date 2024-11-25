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
pkgver=1.0
pkgrel=2
pkgdesc="Holo tmpfiles.d rules for accessing DMI info"
arch=('any')
license=('LGPL2.1')
depends=()
source=('dmi-product-serial.conf')
sha256sums=('a7d2e7787029136ecb4b3bf391873fdc82440edcfd2dcf74f7924cd377fca26b')

package() {
  # Loosen the product_serial node to 440 / root:wheel, rather than 400 / root:root to allow the physical users to read
  # S/N without auth.
  install -D -m644 "$srcdir"/dmi-product-serial.conf "$pkgdir"/usr/lib/tmpfiles.d/dmi-product-serial.conf
}
