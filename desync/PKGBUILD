# Maintainer: David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <denittis@collabora.com>

# Holo: We backport one commit from Desync master.
# Once we'll have the upcoming Desync v1.0.1 in our repos, we can
# drop this custom PKGBUILD.

pkgname=desync
pkgver=1.0.0
pkgrel=1.1
pkgdesc="Alternative casync implementation"
arch=(x86_64)
url="https://github.com/folbricht/desync"
license=(BSD-3-Clause)
depends=(glibc)
makedepends=(go)
options=(!lto)
source=($pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz
        # This patch is already merged upstream, and will be part of next Desync v1.0.1 release
        0001-Avoid-rewriting-self-seed-chunks-already-on-disk.patch
)
sha512sums=('a4f8638492b7eb2f78dd33ddf96ac120e900c6049babae105822ff5248e3398f08fc3880d55128f5e79ab7d78e469793cbd55d8330a86bf51b997402b28cc9a3'
            '5d4f41ca3f3f7070eb38d85b91d606d5b8ecb52af5e1a1af232065bef71bd4659331c6ad1b8075c6dbd1a17cf5f2ce101ab78ff67ac93e5a2396adc6ee279d00')
b2sums=('f304ca105d02d38fe93a5006c6b2b7799065f6db25936838df9242778f8394159d7fc2a2f3ad6b342acc998fd203bcc10c3e001c5726a56af1fa55dbfb0d259f'
        'ea8511ef32c1620c08ac9da9c1f5e40326b8ac1d446ce9dd1b975797620610bc635ac51bbecefec58fbbf05225fce8435bbc66ff4b3e06768082770cb89e813c')

prepare() {
  cd $pkgname-$pkgver
  patch -p1 -i ${srcdir}/0001-Avoid-rewriting-self-seed-chunks-already-on-disk.patch
}

build() {
  export CGO_CPPFLAGS="$CPPFLAGS"
  export CGO_CFLAGS="$CFLAGS"
  export CGO_CXXFLAGS="$CXXFLAGS"
  export CGO_LDFLAGS="$LDFLAGS"
  export GOPATH="$srcdir"
  export GOFLAGS="-buildmode=pie -mod=readonly -modcacherw -buildvcs=false"

  cd $pkgname-$pkgver
  go build -ldflags "-compressdwarf=false -linkmode external" -o $pkgname ./cmd/$pkgname
}

check() {
  cd $pkgname-$pkgver
  go test ./cmd/$pkgname
}

package() {
  cd $pkgname-$pkgver
  install -vDm 755 $pkgname -t "$pkgdir/usr/bin/"
  install -vDm 644 README.md -t "$pkgdir/usr/share/doc/$pkgname/"
  install -vDm 644 LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"
}
