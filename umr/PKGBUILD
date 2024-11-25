# Maintainer: Joshua Ashton <joshua@froggi.es>
# Maintainer: Emil Velikov <emil.l.velikov@gmail.com>

pkgname=umr
_srctag=1.0.10
pkgver=${_srctag##v}
pkgrel=1.1
pkgdesc='userspace debugging and diagnostic tool for AMD GPUs using the AMDGPU kernel driver'
arch=('i686' 'x86_64')
url='https://gitlab.freedesktop.org/tomstdenis/umr'
license=('MIT')
depends=('libpciaccess' 'ncurses' 'llvm-libs')
makedepends=('git' 'cmake' 'llvm' 'libdrm')
source=("git+https://gitlab.freedesktop.org/tomstdenis/umr.git#tag=${_srctag}")
sha256sums=('SKIP')

build() {
	mkdir -p build
	cd build
	cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib -DCMAKE_BUILD_TYPE=Release -DUMR_NO_GUI=ON ../umr
}

package() {
	cd build
	make DESTDIR="$pkgdir" install
	cd ../umr
	install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 LICENSE
}

