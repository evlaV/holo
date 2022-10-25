# Maintainer: Arti Zirk <arti.zirk@gmail.com>

pkgname=rauc
pkgver=1.4
# https://github.com/rauc/rauc/pull/817
pkgrel=6
pkgdesc="RAUC controls the update process on embedded linux systems. It is both a target application that runs as an update client and a host/target tool that allows you to create, inspect and modify installation artifacts."
arch=('i686' 'x86_64')
url="https://github.com/rauc/rauc"
license=('GPL')
depends=('curl' 'json-glib')
optdepends=(
  'casync: Casync integration support'
  'squashfs-tools: Extract or print the info of a bundle'
)
makedepends=('python')
source=(https://github.com/$pkgname/$pkgname/releases/download/v$pkgver/$pkgname-$pkgver.tar.xz
        https://github.com/$pkgname/$pkgname/releases/download/v$pkgver/$pkgname-$pkgver.tar.xz.asc
        0001-src-network-make-the-use-of-.netrc-optional.patch
        0002-Add-casync-install-args-configuration-key.patch
        0003-Add-initial-support-for-desync.patch)
sha256sums=('85aabf214cd93a37f7ad0b3aaad89eb94facf0f3ebf6e2edca945acbca9b0967'
            'SKIP'
            '2bc94a61b342e91c895066d91ef9df3970eed148f99180317a5f1bc203688bd8'
            'f0031c58deb71fe0fee853832c671cfc3e08c5311380a67a838f64713944815f'
            'cef1ec8e4696771ad0bc594aaabfe8a629a18c9b8260715d6fd25a6e3faa7350')
validpgpkeys=('977843FD5C3EBF76BAD4008EA58CC53DBF05E090')

prepare() {
  cd $srcdir/$pkgname-$pkgver
  patch -p1 -i "$srcdir/0001-src-network-make-the-use-of-.netrc-optional.patch"

  # https://github.com/rauc/rauc/pull/817
  patch -p1 -i "$srcdir/0002-Add-casync-install-args-configuration-key.patch"
  patch -p1 -i "$srcdir/0003-Add-initial-support-for-desync.patch"
}

build() {
  cd $srcdir/$pkgname-$pkgver
  ./configure --prefix=/usr
  make
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make DESTDIR=$pkgdir install
}
# vim:syntax=sh
