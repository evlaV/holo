# Maintainer :  gosi <gosi@aon.at>
# Contributor: Vicki Pfau <vi@endrift.com>
# Contributor: bartus <arch-user-repository@bartus.33mail.com>
# Contributor: Lars Hagström <lars@foldspace.nu>
# Contributor: Nephyrin Zey <nephyrin@doublezen.net>
# Contributor: John Schoenick <john@pointysoftware.net>
# Contributor: Geoffrey Teale <tealeg@googlemail.com>

pkgname=breakpad
pkgver=v2024.02.16
pkgrel=1
_lssver=v2024.02.01
pkgdesc="An open-source multi-platform crash reporting system"
arch=('i686' 'x86_64' 'armv7h')
url="https://chromium.googlesource.com/breakpad/breakpad/"
license=('BSD')
makedepends=('git')
depends=('gcc-libs')
provides=('google-breakpad')
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/google/breakpad/archive/refs/tags/${pkgver}.tar.gz"
	"lss-${_lssver}.tar.gz::https://chromium.googlesource.com/linux-syscall-support/+archive/refs/tags/${_lssver}.tar.gz")
noextract=("lss-${_lssver}.tar.gz")
sha256sums=(
    'b1940cd9231822f1d332d1776456afa8d452e59799cbeef70641885c39547b28'
    'SKIP' # This file is constructed on the fly without a consistent hash
)

prepare() {
  mkdir -p "$srcdir/${pkgname}-${pkgver##v}/src/third_party/lss"
  tar xf lss-${_lssver}.tar.gz -C "$srcdir/${pkgname}-${pkgver##v}/src/third_party/lss"
}

build() {
  cd "$srcdir/${pkgname}-${pkgver##v}"

  echo "Configuring"
  autoreconf
  ./configure --prefix=/usr --libexecdir=/usr/lib/${pkgname}
  echo "Building"
  make
}

package() {
  cd "$srcdir/${pkgname}-${pkgver##v}"
  make DESTDIR="$pkgdir" install
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
