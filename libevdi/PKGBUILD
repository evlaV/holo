# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=libevdi
_srctag=1.15.1
pkgver=${_srctag//-/.}
pkgrel=1
pkgdesc="Extensible Virtual Display Interface userland library"
arch=(x86_64)
url="https://github.com/DisplayLink/evdi"
license=('LGPL2.1')
depends=('glibc')
makedepends=('libdrm')
source=("https://github.com/DisplayLink/evdi/archive/refs/tags/v$_srctag.tar.gz")
sha256sums=('b120df303d14be09062157aab17a8598746c0caf2e076ff3388b4091186cf2d9')
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
