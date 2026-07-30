# Maintainer: David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <denittis@collabora.com>

# Holo: Increase the goroutines. This is a temporary workaround until we
# have a proper solution that we can send upstream.

pkgname=desync
pkgver=1.0.3
pkgrel=1.1
pkgdesc="Alternative casync implementation"
arch=(x86_64)
url="https://github.com/folbricht/desync"
license=(BSD-3-Clause)
depends=(glibc)
makedepends=(go)
options=(!lto)
source=($pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz
        # Holo: Increase the number of goroutines. Temp fix that needs to be reworked
        # and sent upstream. Ref https://gitlab.steamos.cloud/holo-team/tasks/-/work_items/2068
        0001-Default-to-100-goroutines-rather-than-10-for-testing.patch
)
sha512sums=('f8cb2ee43bc658fb8018b80c9dfa92732c04a05ca7c08862b781c21bdad61018271c6a4c41bf48d49273262e2fcdbfc5e5d3df3ae5d925ad19b80be159356a19'
            '85c24188a7315befa26dd988926ea8ccca45aaeb7cac30bdb057bf50cbc5a6f40ad336f24a1bde23c9ba6b7f2d93c520fd5ed0a4f7204bb76ec14cc9a28f331e')
b2sums=('9dc1b30cb384d45cea20c37d252a78eb0dc7576f3fb6316ac8295b83a427bbf3eb32bd962a19fac08f566928fc8ed9f2aceb09451f02abf7d6190d87e401817a'
        '70a3513913f660bcf987a190c9e795716861501a00fe8c802dee9363b7c66ca69a5146ddba35db9b8001372d3347fe78ba416440a9d1a7c288313989491c7b77')

prepare() {
  cd $pkgname-$pkgver
  patch -p1 -i "${srcdir}"/0001-Default-to-100-goroutines-rather-than-10-for-testing.patch
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
