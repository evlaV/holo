pkgname=desync-git
pkgver=0.9.2.r19.gb545768
pkgrel=2
pkgdesc="Alternative casync implementation"
arch=(x86_64)
url="https://github.com/folbricht/desync"
license=('BSD')
depends=('fuse2')
makedepends=('git' 'go')
provides=("${pkgname%-git}")
conflicts=("${pkgname%-git}")
source=("${pkgname%-git}::git+${url}.git#commit=b545768")
sha256sums=('SKIP')

pkgver() {
  cd "${pkgname%-git}"
  # cutting off 'v' prefix that presents in the git tag
  git describe --long | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g'
}

build() {
  export CGO_CPPFLAGS="${CPPFLAGS}"
  export CGO_CFLAGS="${CFLAGS}"
  export CGO_CXXFLAGS="${CXXFLAGS}"
  export CGO_LDFLAGS="${LDFLAGS}"
  export GOFLAGS="-buildmode=pie -trimpath -mod=readonly -modcacherw"
  cd "${pkgname%-git}"

  go build -o "${pkgname%-git}" ./cmd/desync
}

package() {
  cd "${pkgname%-git}"
  install -Dm755 ${pkgname%-git} "${pkgdir}"/usr/bin/${pkgname%-git}

  install -Dm644 LICENSE "${pkgdir}"/usr/share/licenses/${pkgname%-git}/LICENSE
}
