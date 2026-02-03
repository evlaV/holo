# Maintainer: AndyRTR <andyrtr at archlinux.org>
# Maintainer : Christian Rebischke <chris.rebischke@archlinux.org>
# Maintainer: Levente Polyak <anthraxx[at]archlinux[dot]org>

pkgname=iwd
pkgver=3.9
pkgrel=1.1
pkgdesc='Internet Wireless Daemon'
arch=('x86_64')
url='https://git.kernel.org/cgit/network/wireless/iwd.git/'
license=('LGPL-2.1-or-later')
depends=('glibc' 'readline' 'libreadline.so' 'ell' 'gcc-libs')
makedepends=('python-docutils' 'dbus' 'systemd')
optdepends=('qrencode: for displaying QR code after DPP is started')
source=(https://www.kernel.org/pub/linux/network/wireless/iwd-${pkgver}.tar{.xz,.sign}
        0001-use-network-group-for-unprivileged-access.diff
        # Holo: one fix is for iwd partial channel scans flushing the kernel BSS cache and
        # one fix is to protect pending BSS ids during the connection process.
        # See https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1978 for details
        # These should be upstreamed after further testing, at which point we can drop our fork.
        0001-station-avoid-flushing-BSS-cache-on-partial-channel-.patch
        0002-station-protect-pending-BSS-during-connection-attemp.patch)
# https://mirrors.edge.kernel.org/pub/linux/network/wireless/sha256sums.asc
sha256sums=('0cd7dc9b32b9d6809a4a5e5d063b5c5fd279f5ad3a0bf03d7799da66df5cad45'
            'SKIP'
            'd5fb4fb864b7a0632117aa2039df535ab5c1d024ae618a1f09e34dfab8ee0cc7'
            'ba4f87cb770d38088260500e52c59500dc67801a625a5cb084598382ce4cf947'
            '8fa1163c9c27b94e5a2efb08a9fc7b53817b729e28f365f36646a51bcb460883')
validpgpkeys=('E932D120BC2AEC444E558F0106CA9F5D1DCF2659')
# https://lore.kernel.org/iwd/20240122104541.74f1a697@workstation64.local/T/#u
options=('!lto')

prepare() {
  cd ${pkgname}-${pkgver}
  # replace Debian "netdev" group with existing "network" group
  # for unprivileged access to iwd - avoid also log spam
  # https://gitlab.archlinux.org/archlinux/packaging/packages/iwd/-/issues/2 + #3
  patch -Np1 -i ../0001-use-network-group-for-unprivileged-access.diff

  # Holo: fix iwd flush expiration behavior
  patch -Np1 -i ../0001-station-avoid-flushing-BSS-cache-on-partial-channel-.patch
  # Holo: protect pending BSS ids during connection
  patch -Np1 -i ../0002-station-protect-pending-BSS-during-connection-attemp.patch

  # https://lore.kernel.org/iwd/20240122105312.66fb4dbf@workstation64.local/T/#u
  # disable one expected test failure - requires a kernel module we cannot load
  # from inside the chroot
  sed -i "s:unit/test-wsc::" Makefile.am
  # and another failing test that depends on AES_CTR not available
  sed -i "s:unit/test-storage::" Makefile.am
  # and more since 3.10 - they don't fail building locally
  sed -i "s:unit/test-crypto::" Makefile.am
  sed -i "s:unit/test-eapol::" Makefile.am
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
