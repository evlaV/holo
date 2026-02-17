# Maintainer: Pierre Schmitz <pierre@archlinux.de>

pkgname=openssl
pkgver=3.5.5
pkgrel=1.1 # Rebuild for holo
pkgdesc='The Open Source toolkit for Secure Sockets Layer and Transport Layer Security'
arch=('x86_64')
url='https://www.openssl.org'
license=('Apache-2.0')
depends=('glibc')
makedepends=('perl')
optdepends=('ca-certificates' 'perl')
replaces=('openssl-perl' 'openssl-doc')
provides=('libcrypto.so' 'libssl.so')
backup=('etc/ssl/openssl.cnf')
source=("https://github.com/${pkgname}/${pkgname}/releases/download/${pkgname}-${pkgver}/${pkgname}-${pkgver}.tar.gz"{,.asc}
        'ca-dir.patch')
sha256sums=('b28c91532a8b65a1f983b4c28b7488174e4a01008e29ce8e69bd789f28bc2a89'
            'SKIP'
            '0a32d9ca68e8d985ce0bfef6a4c20b46675e06178cc2d0bf6d91bd6865d648b7')
validpgpkeys=('EFC0A467D613CB83C7ED6D30D894E2CE8B3D79F5'
              'BA5473A2B0587B07FB27CF2D216094DFD0CB81EF')

prepare() {
	# Holo: Add /usr/bin/core_perl to the PATH so the pod2man binary is found
	PATH=$PATH:/usr/bin/core_perl

	cd "$srcdir/$pkgname-$pkgver"

	# set ca dir to /etc/ssl by default
	patch -Np1 -i "$srcdir/ca-dir.patch"
}

build() {
	cd "$srcdir/$pkgname-$pkgver"

	local _platform="linux-$CARCH"
	case "${CARCH}" in
	"riscv64")
		_platform="linux64-$CARCH"
		;;
	esac


	./Configure --prefix=/usr --openssldir=/etc/ssl --libdir=lib \
		shared enable-ktls enable-ec_nistp_64_gcc_128 ${_platform}

	make depend
	make
}

check() {
	cd "$srcdir/$pkgbase-$pkgver"

	# the test fails due to missing write permissions in /etc/ssl
	# revert this patch for make test
	patch -Rp1 -i "$srcdir/ca-dir.patch"

	if [[ "${CARCH}" == "riscv64" ]] || [[ "${CARCH}" == "aarch64" ]]; then
		# https://github.com/openssl/openssl/issues/12242
		make HARNESS_JOBS=$(nproc) TESTS=-test_afalg test
	else
		make HARNESS_JOBS=$(nproc) test
	fi


	patch -Np1 -i "$srcdir/ca-dir.patch"
	# re-run make to re-generate CA.pl from the patched .in file.
	make apps/CA.pl
}

package() {
	cd "$srcdir/$pkgname-$pkgver"

	make DESTDIR="$pkgdir" MANDIR=/usr/share/man MANSUFFIX=ssl install_sw install_ssldirs install_man_docs

	install -D -m644 LICENSE.txt "$pkgdir/usr/share/licenses/$pkgname/LICENSE.txt"
}
