# Maintainer: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Maintainer: Dan McGee <dan@archlinux.org>
# Maintainer (Holo): Alberto Garcia <berto@igalia.com>

pkgname=libarchive
pkgver=3.7.2
pkgrel=1.1 # Holo: Fix CVE-2024-26256 and two more OOB reads
pkgdesc='Multi-format archive and compression library'
arch=('x86_64')
url='https://libarchive.org/'
license=('BSD')
depends=('acl' 'libacl.so' 'bzip2' 'expat' 'lz4' 'openssl' 'libcrypto.so' 'xz'
         'zlib' 'zstd')
provides=('libarchive.so')
validpgpkeys=('A5A45B12AD92D964B89EEE2DEC560C81CEC2276E'  # Martin Matuska <mm@FreeBSD.org>
              'DB2C7CF1B4C265FAEF56E3FC5848A18B8F14184B') # Martin Matuska <martin@matuska.org>
source=("https://github.com/${pkgname}/${pkgname}/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.xz"{,.asc}
        "fix-cve-2024-26256.patch"
        "fix-oob-rar-1.patch"
        "fix-oob-rar-2.patch")
sha256sums=('04357661e6717b6941682cde02ad741ae4819c67a260593dfb2431861b251acb'
            'SKIP'
            '6d5736c161b41b42e19a49de7d7b5aac1b86112c23ae4ad1b429c0660e8a3ec8'
            '1a54ad569fdd07614df78510a764a5f3a32cf29e7ef42445a74e781d5de1415b'
            '1bbe5a35acf89dd097f5c603aeac1f96793ed7259ba9f9e838e8196fd6b188dd')

prepare() {
    cd "${pkgname}-${pkgver}"
    # Holo: apply downstream patches
    local src
    for src in "${source[@]}"; do
        [[ $src = *.patch ]] || continue
        src="${src##*/}"
        echo "Applying patch $src..."
        patch -Np1 < "../$src"
    done
}

build() {
  cd "${pkgname}-${pkgver}"

  ./configure \
      --prefix=/usr \
      --without-xml2 \
      --without-nettle \
      --disable-static
  make
}

check() {
  cd "${pkgname}-${pkgver}"

  make check
}

package() {
  cd "${pkgname}-${pkgver}"

  make DESTDIR="$pkgdir" install
  install -Dm0644 COPYING "$pkgdir/usr/share/licenses/libarchive/COPYING"
}
