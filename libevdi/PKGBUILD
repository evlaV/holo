# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=libevdi
_srctag=1.14.10
pkgver=${_srctag//-/.}
pkgrel=1
pkgdesc="Extensible Virtual Display Interface userland library"
arch=(x86_64)
url="https://github.com/DisplayLink/evdi"
license=('LGPL2.1')
depends=('glibc')
makedepends=('libdrm')
source=("https://github.com/DisplayLink/evdi/archive/refs/tags/v$_srctag.tar.gz")
sha256sums=('9fc0165d02e88507135d6a67ccaa06f7b5cd651e375394a1674d5ea4ec7a00aa')
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
