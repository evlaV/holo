# Maintainer: Vicki Pfau <vi@endrift.com>

pkgname=libevdi
_srctag=1.12.0
pkgver=${_srctag//-/.}
pkgrel=2
pkgdesc="Extensible Virtual Display Interface userland library"
arch=(x86_64)
url="https://github.com/DisplayLink/evdi"
license=('LGPL2.1')
depends=('glibc')
makedepends=('libdrm')
source=("https://github.com/DisplayLink/evdi/archive/refs/tags/v$_srctag.tar.gz")
sha256sums=('484b1166ac1eccd14ec2c88ba426089d001401ba33612620d38d5f214a809fef')
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
