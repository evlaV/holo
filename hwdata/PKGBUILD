# Maintainer: Tobias Powalowski <tpowa@archlinux.org>

# Holo: Backport the name change for the 15e3 AMD APU audio controller
# We can go back to the Arch Linux upstream package once we have hwdata 0.402 or newer

pkgname=hwdata
pkgver=0.397
pkgrel=1.1
pkgdesc="hardware identification databases"
makedepends=('git')
replaces=('hwids')
url=https://github.com/vcrhonek/hwdata
license=('GPL-2.0-or-later')
arch=('any')
source=("git+https://github.com/vcrhonek/hwdata.git#tag=v${pkgver}?signed"

        # Holo: Backport the name change for the 15e3 AMD APU audio controller
        # Upstream change from https://admin.pci-ids.ucw.cz/read/PC/1022/15e3 and
        # https://github.com/pciutils/pciids/commit/282d63a312f443378019740728c9b565cce5dc9e
        # Addresses https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1891
        "0001-Update-the-15e3-HD-Audio-Controller-name.patch")
validpgpkeys=('3C40194FB79138CE0F78FD4919C2F062574F5403') # Vitezslav Crhonek
b2sums=('3b57d8314c47eebfe3f4a77a902a44b75d2e2711c335d5809697a99c00e4a28b7d04f644d30eb26f2c0cea3bbe506f87179ce3a9cd4e8d3e27a73959aabfde49'
        '916cf55e042e43f59065b47f1e010a7439f9d84819c967ce25194f72fd07b73972d2f7d7458a6b255495e44508c4fdc97a9ce5eea61d6d5351d30923b76549e4')

prepare() {
  cd ${pkgname}
  patch -p1 -i ${srcdir}/0001-Update-the-15e3-HD-Audio-Controller-name.patch
}

build() {
  cd ${pkgname}
  ./configure --prefix=/usr --disable-blacklist
}

package() {
  cd ${pkgname}
  make DESTDIR="${pkgdir}" install
}
