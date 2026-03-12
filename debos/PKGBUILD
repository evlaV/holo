pkgname=debos
epoch=1
pkgver=1.1.7
pkgrel=1
pkgdesc="OS images builder"
arch=(x86_64)
url="https://github.com/go-debos/${pkgname}"
license=('Apache')
depends=('ostree' 'busybox' 'qemu-base')
makedepends=('git' 'go' 'openssh')
provides=("${pkgname}-git")
conflicts=("${pkgname}-git")
# NOTE: Keep the URL/branch in the README in sync
source=("git+https://github.com/go-debos/debos#tag=v${pkgver}"
	# These patches are already merged upstream, and will be part of next debos v1.1.8 release
        "0001-actions-overlay-Allow-absolute-paths-in-overlay.patch"
        "0002-actions-overlay-test-absolute-path-handling.patch"
)
sha256sums=('2031879ade11c222070b52b8af355966676285a0752a529ec3b87c5ab5f35571'
            'f6798067046906d95f7d1b9717b353f5a692696f4ea1cca6227f5597f1fa14d9'
            'e98f74aa6516fc9bd958220368707d525f9957fd4b8d199935886657b4fbe45f'
)

prepare() {
  cd "$srcdir"/${pkgname}
  patch -p1 -i "$srcdir"/0001-actions-overlay-Allow-absolute-paths-in-overlay.patch
  patch -p1 -i "$srcdir"/0002-actions-overlay-test-absolute-path-handling.patch
}

build() {
  export CGO_CPPFLAGS="${CPPFLAGS}"
  export CGO_CFLAGS="${CFLAGS}"
  export CGO_CXXFLAGS="${CXXFLAGS}"
  export CGO_LDFLAGS="${LDFLAGS}"
  export GOFLAGS="-buildmode=pie -trimpath -mod=readonly -modcacherw"
  cd "${pkgname}"

  go build ./cmd/debos/
}

package() {
  cd "${pkgname}"
  install -Dm755 ${pkgname} "${pkgdir}"/usr/bin/${pkgname}
}
