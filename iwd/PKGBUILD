# Maintainer : Christian Rebischke <chris.rebischke@archlinux.org>
# Maintainer: Levente Polyak <anthraxx[at]archlinux[dot]org>
# Contributor: AndyRTR <andyrtr at archlinux.org>

pkgname=iwd
pkgver=2.14
pkgrel=1.3
pkgdesc='Internet Wireless Daemon'
arch=('x86_64')
url='https://git.kernel.org/cgit/network/wireless/iwd.git/'
license=('LGPL-2.1-or-later')
depends=('glibc' 'readline' 'libreadline.so' 'ell' 'gcc-libs')
makedepends=('python-docutils' 'dbus' 'systemd'
  'python>=3.11'
  'python<3.12'
)
optdepends=('qrencode: for displaying QR code after DPP is started')
source=(https://www.kernel.org/pub/linux/network/wireless/iwd-${pkgver}.tar{.xz,.sign}
        # replace Debian "netdev" group with existing "network" group
        # for unprivileged access to iwd - avoid also log spam
        # https://gitlab.archlinux.org/archlinux/packaging/packages/iwd/-/issues/2 + #3
        0001-use-network-group-for-unprivileged-access.diff
        0002-Register-EAPOL-frame-listeners-earlier.patch # fixed upstream in 2.17
        # https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1419
        # https://lore.kernel.org/iwd/26febdbb-1184-46be-989b-45aace86f104@collabora.com/T/#u
        0003-allow-duplicate-ie-rsnx.patch
)
# https://mirrors.edge.kernel.org/pub/linux/network/wireless/sha256sums.asc
sha256sums=('830184db5d3885ac68701cd8bb1c04d0bd8c8d3ab1c82b893b5e2bdf23329f28'
            'SKIP'
            'd5fb4fb864b7a0632117aa2039df535ab5c1d024ae618a1f09e34dfab8ee0cc7'
            '9a7d15b82f8837dc8ecb33b4e3c6a27b30cffd1adbb648bbba86bbf317f5dfe7'
            '20a5740e5004c2e78c2f8ecabd752d256f8b1addc0eb91fcb34aefc5b93e9b68'
)
validpgpkeys=('E932D120BC2AEC444E558F0106CA9F5D1DCF2659')
# Tests use ell in a way that is incompatible with LTO.
# https://lore.kernel.org/iwd/20240122104541.74f1a697@workstation64.local/T/#u
options=('!lto')

prepare() {
  cd ${pkgname}-${pkgver}
  for _patch in "${source[@]}"
  do
    case $_patch in
      *.patch|*.diff)
        echo "Applying $_patch"
        patch -Np1 -i ../$_patch
        ;;
    esac
  done

  # https://lore.kernel.org/iwd/20240122105312.66fb4dbf@workstation64.local/T/#u
  # disable one expected test failure - requires a kernel module we cannot load
  # from inside the chroot
  sed -i "s:unit/test-wsc::" Makefile.am
  autoreconf -vfi
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
  make check
}

package() {
  cd ${pkgname}-${pkgver}
  make install DESTDIR="${pkgdir}"
  install -Dm 644 README -t "${pkgdir}/usr/share/doc/${pkgname}"
}
