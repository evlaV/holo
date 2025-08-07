# Maintainer: Joshua Ashton <joshua@froggi.es>
# Maintainer: Emil Velikov <emil.l.velikov@gmail.com>

pkgname=umr
_srctag=1.0.10
pkgver=${_srctag##v}
pkgrel=1.3
pkgdesc='userspace debugging and diagnostic tool for AMD GPUs using the AMDGPU kernel driver'
arch=('i686' 'x86_64')
url='https://gitlab.freedesktop.org/tomstdenis/umr'
license=('MIT')
depends=('libpciaccess' 'ncurses' 'llvm-libs')
makedepends=('git' 'cmake' 'llvm' 'libdrm')
source=("git+https://gitlab.freedesktop.org/tomstdenis/umr.git#tag=${_srctag}"
        '0001-Skip-processing-IBs-if-stack-is-exhausted.patch'
        '0002-Bump-ring-stream-decoder-stack-size.patch')
sha256sums=('SKIP'
            '3c4728ddeaa6ad08323516574ae7929ba8ac47313328d386c7a0396610fa2259'
            'd5d259fa2a2564228177d90ee0f3370db88b50a5a2b4f5b625e255901ef1c06f')

prepare() {
	patch -p1 -d umr < 0001-Skip-processing-IBs-if-stack-is-exhausted.patch
	patch -p1 -d umr < 0002-Bump-ring-stream-decoder-stack-size.patch
}

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

