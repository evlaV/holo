# Maintainer: Baris Demirdelen <barisdemirdelen at gmail dot com>

pkgname=xow-git
_pkgname=xow
pkgver=0.5.r28.ga396e3f
# Patches to use external (user provided) firmware blob.
# Upstream MR https://github.com/medusalix/xow/pull/172
pkgrel=2
epoch=1
pkgdesc="Linux driver for the Xbox One wireless dongle"
arch=(x86_64)
url=https://github.com/medusalix/xow
license=('GPL2')
depends=(libusb bash xdg-utils zenity curl cabextract coreutils polkit)
makedepends=('git')
source=('git+https://github.com/medusalix/xow#commit=a396e3f'
	# Patches to use external (user provided) firmware blob.
	# Upstream MR https://github.com/medusalix/xow/pull/172
	'steamos-0001-Store-the-firmware-blob-in-Mt76-firmware.patch'
	'steamos-0002-Load-the-firmware-file-from-disk.patch'
	'steamos-0003-Introduce-xow-get-firmware.sh-script.patch'
	'steamos-0004-makefile-install-depends-on-all.patch'
	'steamos-0005-makefile-fixup-xow.service-handling.patch')

sha256sums=('SKIP'
            'd3450919133b4acbdf3f9ed8a99a1ee9793de22a808e438b11e0eace50ea291d'
            'a9870212f12faae668ef7deb97c297965499830ff39791f771e689b59bdc64f7'
            '7e926276653b5f913834f381d0d25b400d7024c8300a0b659ad1275686b0d71f'
            '6e4d57ef3a23e9b073b069625316059de2280b936bb3c62fbaf3b281f6fd93c6'
            '3bcfb88b12f6821431bc01e0736f05ab86a0704897de4fa4d2a612e97d5d3608')

pkgver() {
  cd $srcdir/$_pkgname
  git describe --long --tags | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g'
}

prepare() {
  cd $srcdir/$_pkgname

  patch -p1 -i $srcdir/steamos-0001-Store-the-firmware-blob-in-Mt76-firmware.patch
  patch -p1 -i $srcdir/steamos-0002-Load-the-firmware-file-from-disk.patch
  patch -p1 -i $srcdir/steamos-0003-Introduce-xow-get-firmware.sh-script.patch
  patch -p1 -i $srcdir/steamos-0004-makefile-install-depends-on-all.patch
  patch -p1 -i $srcdir/steamos-0005-makefile-fixup-xow.service-handling.patch
}

build() {
  cd $srcdir/$_pkgname
  make PREFIX=/usr BUILD=RELEASE
}

package() {
  cd $srcdir/$_pkgname

  make PREFIX=/usr DESTDIR=$pkgdir/ SYSDDIR=/usr/lib/systemd/system install
}
