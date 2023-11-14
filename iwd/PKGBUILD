# Maintainer : Christian Rebischke <chris.rebischke@archlinux.org>
# Maintainer: Levente Polyak <anthraxx[at]archlinux[dot]org>
# Contributor: AndyRTR <andyrtr at archlinux.org>
# Maintainer (Holo): Emil Velikov <emil.l.velikov@gmail.com>

pkgname=iwd
pkgver=2.7
# Holo: backport OWE AKM fix
pkgrel=1.2
pkgdesc='Internet Wireless Daemon'
arch=('x86_64')
url='https://git.kernel.org/cgit/network/wireless/iwd.git/'
license=('LGPL')
depends=('glibc' 'readline' 'libreadline.so' 'ell' 'gcc-libs')
makedepends=('python-docutils' 'dbus' 'systemd')
optdepends=('qrencode: for displaying QR code after DPP is started')
source=("https://www.kernel.org/pub/linux/network/wireless/iwd-${pkgver}.tar"{.xz,.sign}
# https://mirrors.edge.kernel.org/pub/linux/network/wireless/sha256sums.asc
# Holo: backport OWE AKM fix
        0001-netdev-relax-requirement-for-OWE-AKM-in-assoc-reply.patch)
sha256sums=('289ff47a76fb854e7789c45c5e3e0f15de4adc5fd2e82e47ab08e3564d8961d9'
            'SKIP'
            '561ba42ed2b3a03166bb68ba8b1273a8585c5c2a3eb603b89ad3f17bfab45876')
validpgpkeys=('E932D120BC2AEC444E558F0106CA9F5D1DCF2659')
changelog=ChangeLog
install=iwd.install

prepare() {
  cd ${pkgname}-${pkgver}

  local src
  for src in "${source[@]}"; do
    src="${src%%::*}"
    src="${src##*/}"
    [[ $src = *.patch ]] || continue
    echo "Applying patch $src..."
    patch -Np1 < "../$src"
  done
}

build() {
  cd ${pkgname}-${pkgver}
	dbus-run-session ./configure --prefix=/usr \
	--sysconfdir=/etc \
	--localstatedir=/var \
	--libexecdir=/usr/lib/iwd \
	--enable-external-ell \
	--enable-wired \
	--enable-ofono \
	--enable-hwsim \
	--disable-tools
  make
}

check() {
  cd ${pkgname}-${pkgver}
  # pass broken tests - should reported upstream
  # One test fail because we need kernel capabilities that
  # we don't have inside of systemd-nspawn
  # this could only be fixed via changing our build environment
  make -k check || /bin/true
}

package() {
  cd ${pkgname}-${pkgver}
  make install DESTDIR="${pkgdir}"
  install -Dm 644 README -t "${pkgdir}/usr/share/doc/${pkgname}"
}

# vim: ts=2 sw=2 et:
