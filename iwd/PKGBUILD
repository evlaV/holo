# Maintainer : Christian Rebischke <chris.rebischke@archlinux.org>
# Maintainer: Levente Polyak <anthraxx[at]archlinux[dot]org>
# Contributor: AndyRTR <andyrtr at archlinux.org>

# NOTE: FORK from Arch
pkgname=iwd
pkgver=1.30
# SteamOS: the cipher patches from upstream/master branch
# These are expected to be in the next release aka 1.31
pkgrel=1.2
pkgdesc='Internet Wireless Daemon'
arch=('x86_64')
url='https://git.kernel.org/cgit/network/wireless/iwd.git/'
license=('LGPL')
depends=('glibc' 'readline' 'libreadline.so' 'ell')
makedepends=('python-docutils' 'dbus' 'systemd')
options=('debug')
source=("https://www.kernel.org/pub/linux/network/wireless/iwd-${pkgver}.tar"{.xz,.sign}
# SteamOS: the cipher patches from upstream/master branch
# These are expected to be in the next release aka 1.31
# NOTE: the documentation and auto-tests have been omitted, since they cause
# merge conflicts.
        0001-eapol-More-strictly-validate-key_descriptor_version.patch
        0002-crypto-Rename-BIP-to-BIP_CMAC.patch
        0003-ie-Rename-_BIP-to-_BIP_CMAC.patch
        0004-ie-Simplify-implementation.patch
        0005-crypto-Add-new-cipher-definitions.patch
        0006-ie-Skip-unknown-pairwise-ciphers.patch
        0007-netdev-Build-RSN-attributes-in-a-common-function.patch
        0008-netdev-Add-support-for-setting-GCMP-keys.patch
        0009-ie-Add-support-for-GCMP-cipher-suite.patch
        0010-ie-add-ie_rsn_cipher_suite_to_string.patch
        0011-wiphy-Generalize-supported-cipher-dumper.patch
        0012-wiphy-Support-GCMP-cipher-suite.patch
        0014-station-diagnostic-implement-PairwiseCipher.patch
        0016-ie-Add-support-for-GCMP-CCMP-256.patch
        0017-netdev-Add-support-for-CCMP-GCMP-256.patch
        0018-ie-Add-IE_CIPHER_IS_GCMP_CCMP-inline.patch
        0019-station-Use-IE_CIPHER_IS_GCMP_CCMP.patch
        0020-wiphy-Support-GCMP-CCMP-256-cipher-suites.patch
        0023-ie-Support-more-group-management-cipher-suites.patch
        0024-netdev-Support-more-IGTK-cipher-suites.patch
        0025-wiphy-Support-more-group-management-cipher-suites.patch
        0027-ap-Limit-pairwise-and-group-ciphers-to-CCMP-TKIP.patch
)
# https://mirrors.edge.kernel.org/pub/linux/network/wireless/sha256sums.asc
sha256sums=('9fd13512dc27d83efb8d341f7df98f5488f70131686021fcd0d93fc97af013b8'
            'SKIP'
            '7ed394db089744a0cc38b81963a88fa0ed20d40394e53642d12a47e69966b463'
            'c69f1a98a4682fbf6a8748d7b9cc6ee7217c24b479417121d92db73a3f1a7beb'
            'a6ddf112733fb7ab16752abb24448a7f2375a1f28091ff7a3d4ad81ea8812b3f'
            'c2bbf49d83c0396fb531f611f6eb088a77368fc92d7c8f21e37e3e2753203cfc'
            '647b0f6b5325eb3b372c41ec6a6a0e800fa8c5f6d956f9a8d14a8535050eb6c7'
            '98c43fd0ed01b88485bf65231623f0a7930deb09e5a0df456cd02ffdc7056c52'
            '683ce0492a5df22166626a17925fe6f197f2e9ec7e9460627329e9e202462e5f'
            '0865f40523cf907883410d8bfa60db3ec2b7b284470435e1fb55ec9dedcec0e5'
            'ee1226cffef6fbc55bff450f60523fb899b7661b056632ac5357d269c34cf037'
            '3e9ad9ded2e6438ce0f01cb0f0d62fc35fa1480c610051f619d0bb56a74f0b81'
            '38bb7bb7f7965fd37d97c6b476f3542d24bea44169b10eeb22d0197d8d7f5d99'
            '362374d831b77bd09c10d6c81474060633a1c6dd95d06f5334f504475e7f9218'
            '56a53a1ba838a5c1d2ee2b347688957a9e0ed177c0236ca80f49c444d6d8e3ff'
            'c5c872b3871d9cf71156b183dc3ce8e252f38654147ee0c50d743d6fe8e1d8dc'
            'c4192e48af27585d68c4d4cfab7a856631e07d547005fb08ed2026bf1551a136'
            'eff2eda185888b8fd536b18e8bdb6b7256f03ee1a17b1285d98446964a673251'
            'd281b69b083716b0072a3188196569dccfbaf7b7269c642aa6a740d12d1086d1'
            'a1807344d51299b18141397697881be0f7048b110bd86a2d233d5b50968657ee'
            '5c6c3c91053ea14dd192bec89376ecbbb9ba15d018f331d9a284d7580ec1c55d'
            'e85c50cf3e699f47a8ea6bdb99395dc6bb243fe790f727ceb6b1c76cc0977c3c'
            '82c1cc9363c1f6f54517501e7ab50cd444a1726332259bc3e6eab775e29378b6'
            '26071562e00af9cc083afedb8824016d47b1439264d689a07de34e31bc08a280')
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
