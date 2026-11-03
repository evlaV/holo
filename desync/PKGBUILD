# Maintainer: David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <denittis@collabora.com>

# Holo: Increase the goroutines. This is a temporary workaround until we
# have a proper solution that we can send upstream.

pkgname=desync
pkgver=1.1.5
pkgrel=1.1
pkgdesc="Alternative casync implementation"
arch=(x86_64)
url="https://github.com/folbricht/desync"
license=(BSD-3-Clause)
depends=(glibc)
makedepends=(go)
options=(!lto)
source=($pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz
        # Holo: Increase the number of goroutines. Temporary fix until we use the
        # new adaptive the launch option `-n -1` from RAUC.
        # Ref https://gitlab.steamos.cloud/holo-team/tasks/-/work_items/2068
        0001-Default-to-100-goroutines-rather-than-10-for-testing.patch
)
sha512sums=('e899db5cf38d5b567ca75671508348c01ff859fa19a860324e49e3ab7c9b72a2ac6a527dc6185c05743c2dba70436f4c4239d3d46532eb53a7ec7f80ea28e51b'
            'ca23c3103394c140a96bf3e047ef898c478a9db7136cb2b6cf7399a9eb83e05856fc94e6f4a8390a40a188bf93ae1a225e1c8a4e9141b0b89d8b7ef5959194d6')
b2sums=('7f0b173a709ca78a6c5eb569646c3a8cee48bc3825cb04523c1e6af87a48550e2b13e7406722439041de38af41265c380447d97783f1da02e4f5fe14e181b7be'
        '2a575c3629b88162229b87d3289afc321bb85901a16326d6246c3dbcf3adc460913c1b2c243fa2734d7704fed1599e4623ec1e3ed86f7bfc8d4ceab2d841a7fa')

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

  mkdir --parents --verbose completions manpage
  ./$pkgname completion bash > completions/$pkgname
  ./$pkgname completion fish > completions/$pkgname.fish
  ./$pkgname completion zsh > completions/_$pkgname
  ./$pkgname manpage --section 1 manpage/
}

check() {
  cd $pkgname-$pkgver
  go test ./cmd/$pkgname
}

package() {
  cd $pkgname-$pkgver
  install -vDm 755 $pkgname -t "$pkgdir/usr/bin/"
  install -vDm 644 completions/$pkgname -t "$pkgdir/usr/share/bash-completion/completions/"
  install -vDm 644 completions/$pkgname.fish -t "$pkgdir/usr/share/fish/vendor_completions.d/"
  install -vDm 644 completions/_$pkgname -t "$pkgdir/usr/share/zsh/site-functions/"
  install -vDm 644 manpage/*.1 -t "$pkgdir/usr/share/man/man1/"
  install -vDm 644 README.md -t "$pkgdir/usr/share/doc/$pkgname/"
  install -vDm 644 LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"
}
