# Maintainer: David Runge <dvzrv@archlinux.org>
# Maintainer: Levente Polyak <anthraxx@archlinux.org>
# Contributor: Pierre Schmitz <pierre@archlinux.de>

pkgbase=zlib
pkgname=(
  zlib
  zlib-static
  minizip
)
epoch=1
pkgver=1.4
pkgrel=1.1 # Rebuild for Holo
pkgdesc='Compression library implementing the deflate compression method found in gzip and PKZIP'
arch=(x86_64)
license=(Zlib)
url="https://www.zlib.net/"
source=(https://github.com/madler/zlib/releases/download/v$pkgver/$pkgname-$pkgver.tar.xz{,.asc})
sha512sums=('c6701ef216f2ea451056466794c520df62af0a7ddf57c907c3263678dc625f3d6466e0187106dec0d7721ad6fc6cf105e0f93a4cac82fbcc2ba919eebd29c0b0'
            'SKIP')
b2sums=('2564e092d3daf5c727eddab8785cccf64275d8d534cce96ba6d21fa5c891a135ff5c9b21685a5c549f2c1c790b4ec3ed11449f9bc3da7f5df6b930c4b2f45f03'
        'SKIP')
validpgpkeys=('5ED46A6721D365587791E2AA783FCD8E58BCAFBA')  # Mark Adler <madler@alumni.caltech.edu>

prepare() {
  cd $pkgbase-$pkgver/contrib/minizip
  cp Makefile Makefile.orig
  cp ../README.contrib readme.txt

  autoreconf -fiv
  # NOTE: We are not running autoreconf for the top-level project, because `configure` is a custom script.
}

build() {
  cd $pkgbase-$pkgver

  CFLAGS+=" -ffat-lto-objects"
  ./configure --prefix=/usr
  make

  cd contrib/minizip
  ./configure --prefix=/usr --enable-static=no
  make
}

check() {
  make test -C $pkgbase-$pkgver

  make -f Makefile.orig test -C $pkgbase-$pkgver/contrib/minizip
}

_pick() {
  local p="$1" f d; shift
  for f; do
    d="$srcdir/$p/${f#$pkgdir/}"
    mkdir -p "$(dirname "$d")"
    mv "$f" "$d"
    rmdir -p --ignore-fail-on-non-empty "$(dirname "$f")"
  done
}

package_zlib() {
  depends=(glibc)
  provides=(libz.so)

  make install DESTDIR="$pkgdir" -C $pkgbase-$pkgver
  install -D -m644 $pkgbase-$pkgver/LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"

  cd "$pkgdir"
  _pick $pkgbase-static usr/lib/libz.a
}

package_zlib-static() {
  pkgdesc+=" - static library"
  depends=(
    glibc
    zlib
  )
  options=(staticlibs)

  mv -v $pkgbase-static/* "$pkgdir"
  install -vDm 644 $pkgbase-$pkgver/LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"
}

package_minizip() {
  pkgdesc='Mini zip and unzip based on zlib'
  depends=(
    glibc
    zlib
  )

  make install DESTDIR="$pkgdir" -C $pkgbase-$pkgver/contrib/$pkgname
  install -D -m644 $pkgbase-$pkgver/LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"

  # https://github.com/madler/zlib/pull/229
  rm "$pkgdir/usr/include/minizip/crypt.h"
}

# vim: ts=2 sw=2 et:
