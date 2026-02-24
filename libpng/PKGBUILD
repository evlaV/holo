# Maintainer: Christian Hesse <mail@eworm.de>
# Contributor: Jan de Groot <jgc@archlinux.org>
# Contributor: dorphell <dorphell@archlinux.org>
# Contributor: Travis Willard <travis@archlinux.org>
# Contributor: Douglas Soares de Andrade <douglas@archlinux.org>

pkgname=libpng
pkgver=1.6.55
pkgrel=1.1 # Rebuild for Holo
pkgdesc='A collection of routines used to create PNG format graphics files'
arch=('x86_64')
url='http://www.libpng.org/pub/png/libpng.html'
license=('libpng-2.0')
depends=('zlib' 'sh')
makedepends=('git')
provides=('libpng16.so')
source=("git+https://github.com/pnggroup/libpng.git?signed#tag=v${pkgver}?signed")
sha256sums=('aadb3e69cbc28b1e4f6bdd9fe6bc27487253121a7bde1e26068973002d5fe260')
validpgpkeys=('F57A55036A4D45837074FD92C9E384533403C2F8'  # Cosmin Truta <ctruta@gmail.com>
              '1FED507E3236B4A6E53E922BB292C64843FF5BCF') # Cosmin Truta <ctruta@gmail.com>


prepare() {
  cd $pkgname

  autoreconf -fiv
}

build() {
  cd $pkgname

  ./configure \
    --prefix=/usr \
    --disable-static
  make
}

check() {
  cd $pkgname

  make check
}

package() {
  cd $pkgname

  make DESTDIR="$pkgdir" install

  install -D -m0644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"

  cd contrib/pngminus
  make PNGLIB_SHARED="-L$pkgdir/usr/lib -lpng" CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" png2pnm pnm2png
  install -m0755 png2pnm pnm2png "$pkgdir/usr/bin/"
}
