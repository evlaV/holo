# Maintainer: Joshua Ashton <joshua@froggi.es>
# Maintainer: Emil Velikov <emil.l.velikov@gmail.com>

pkgname=umr
_srctag=1.0.10
pkgver=${_srctag##v}
pkgrel=1.4
pkgdesc='userspace debugging and diagnostic tool for AMD GPUs using the AMDGPU kernel driver'
arch=('i686' 'x86_64')
url='https://gitlab.freedesktop.org/tomstdenis/umr'
license=('MIT')
depends=('libpciaccess' 'ncurses' 'llvm-libs')
makedepends=('git' 'cmake' 'llvm' 'libdrm')
source=("git+https://gitlab.freedesktop.org/tomstdenis/umr.git#tag=${_srctag}"
        '0001-Skip-processing-IBs-if-stack-is-exhausted.patch'
        '0002-Bump-ring-stream-decoder-stack-size.patch'
        # Holo: This patch adds decompression of the database files into /var/tmp/umr as needed for
        # https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1254 as discussed here:
        # https://gitlab.freedesktop.org/tomstdenis/umr/-/merge_requests/69
        '0003-Use-libarchive-to-decompress-database-files-if-neede.patch')
sha256sums=('a5abe9dbd91fe93696005a0b3b2bf111c0c4b5a65ed33529bdbca47edd9204f4'
            '3c4728ddeaa6ad08323516574ae7929ba8ac47313328d386c7a0396610fa2259'
            'd5d259fa2a2564228177d90ee0f3370db88b50a5a2b4f5b625e255901ef1c06f'
            'e4cb774ff18a1ec33df4e22774c116a623526f35b58be8b10ee4e44e6410e29a')

prepare() {
	patch -p1 -d umr < 0001-Skip-processing-IBs-if-stack-is-exhausted.patch
	patch -p1 -d umr < 0002-Bump-ring-stream-decoder-stack-size.patch
	patch -p1 -d umr < 0003-Use-libarchive-to-decompress-database-files-if-neede.patch
}

build() {
	mkdir -p build
	cd build
	cmake \
		-DCMAKE_INSTALL_PREFIX=/usr \
		-DCMAKE_INSTALL_LIBDIR=lib \
		-DCMAKE_BUILD_TYPE=Release \
		-DUMR_NO_GUI=ON \
		-DCOMPRESS_DATABASE_FILES=ON \
		../umr
}

package() {
	cd build
	make DESTDIR="$pkgdir" install
	cd ../umr
	install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 LICENSE
}

