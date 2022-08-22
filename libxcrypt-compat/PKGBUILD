# Maintainer:  twa022 <twa022 at gmail dot com>
# Contributor: Alexander Epaneshnikov <alex19ep@archlinux.org>
# Contributor: Christian Hesse <mail@eworm.de>

_pkgname=libxcrypt
pkgname=${_pkgname}-compat
pkgver=4.4.27
pkgrel=1
pkgdesc='Modern library for one-way hashing of passwords: legacy API functions'
arch=('x86_64')
url='https://github.com/besser82/libxcrypt/'
license=('GPL')
depends=('glibc' 'libxcrypt')
provides=('libcrypt.so.1')
options=(!emptydirs)
validpgpkeys=('678CE3FEE430311596DB8C16F52E98007594C21D') # Björn 'besser82' Esser
source=("${url}/releases/download/v${pkgver}/${_pkgname}-${pkgver}.tar.xz"{,.asc})
sha256sums=('500898e80dc0d027ddaadb5637fa2bf1baffb9ccd73cd3ab51d92ef5b8a1f420'
            'SKIP')

build() {
  cd ${_pkgname}-${pkgver}
  ./configure \
    --prefix=/usr \
    --disable-static \
    --enable-hashes=strong,glibc \
    --enable-obsolete-api=glibc \
    --disable-failure-tokens
  make
}

#check() {
#  cd ${_pkgname}-${pkgver}
#  make check 
#}

package() {
  cd ${_pkgname}-${pkgver}
  make DESTDIR="$pkgdir" install
  rm -r "$pkgdir"/usr/{include,share/man,lib/pkgconfig}
  rm "$pkgdir"/usr/lib/lib{,x}crypt.so
}
