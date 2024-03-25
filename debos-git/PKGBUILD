pkgname=debos-git
epoch=1
pkgver=1.0.0.r255.gf3759a5
pkgrel=3
pkgdesc="OS images builder"
arch=(x86_64)
url="https://github.com/go-debos/${pkgname%-git}"
license=('Apache')
depends=('ostree' 'busybox' 'qemu-base')
makedepends=('git' 'go')
provides=("${pkgname%-git}")
conflicts=("${pkgname%-git}")
# NOTE: Keep the URL/branch in the README in sync
source=("git+https://gitlab.collabora.com/archlinux/${pkgname%-git}.git#commit=f3759a52")
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

	go build ./cmd/debos/
}

package() {
	cd "${pkgname%-git}"
	install -Dm755 ${pkgname%-git} "${pkgdir}"/usr/bin/${pkgname%-git}
}
