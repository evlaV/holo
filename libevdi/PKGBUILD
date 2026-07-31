# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=libevdi
_srctag=1.15.0
pkgver=${_srctag//-/.}
pkgrel=1
pkgdesc="Extensible Virtual Display Interface userland library"
arch=(x86_64)
url="https://github.com/DisplayLink/evdi"
license=('LGPL2.1')
depends=('glibc')
makedepends=('libdrm')
source=("https://github.com/DisplayLink/evdi/archive/refs/tags/v$_srctag.tar.gz")
sha256sums=('c19cd1120b43a0d88e91cdd893b592a56b9a904ead25ea8299eb4b451f649899')
conflicts=('evdi')
provides=("evdi=$pkgver")

build() {
  cd "evdi-$_srctag/library"

  make
}

package() {
  cd "evdi-$_srctag/library"

  make install DESTDIR="$pkgdir" PREFIX='/usr'
}
