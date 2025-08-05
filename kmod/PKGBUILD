# Maintainer:  Holo Team
# Contributor: Dave Reisner <dreisner@archlinux.org>

pkgname=kmod
pkgver=34.2
# SteamOS use /usr/lib/steamos/modules
pkgrel=1.1
pkgdesc="Linux kernel module management tools and library"
arch=('x86_64')
url='https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git'
license=('LGPL-2.1-or-later' 'GPL-2.0-or-later')
depends=('glibc' 'zlib' 'openssl' 'xz' 'zstd')
makedepends=('git' 'meson' 'scdoc')
checkdepends=('linux-headers' 'libelf')
options=('strip')
provides=('libkmod.so')
validpgpkeys=('EAB33C9690013C733916AC839BA2A5A630CBEA53')  # Lucas DeMarchi
source=("git+https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git#tag=v${pkgver}?signed"
        'depmod-search.conf'
        'depmod.hook'
        'depmod.script'

        # Holo: import upstream patch that allows KDIR=any
        # should be part of the upcoming v35
        'ea67bad278e4b613d1420d30ece7de121221eec9.patch'
)
sha256sums=('7eef327c5cbe2a4649b2487b7a5bec6787cd26c9488bdbb2f35beb15305455b1'
            '1a92bfeae870f61ce814577e69d2a147a9c0caf6aed1131243e4179241fcc4a8'
            '4c96f1fda1b4893d03e0ce2c377442bb39e30cd76a85103ede4e93b7d1d5701d'
            '18661aa40c25580f04d2ac3f32e54c2997c0994d1c829905537b413a9d291ac6'
            '2225f3684e79ed06bd7547809a20b13b1f6e43bd1c460b043344f9a696ba746d')

prepare() {
  for patch in "${source[@]}"
  do
    case $patch in
      *.patch)
        echo "# Applying ${patch}"
        patch -d "${pkgname}" -p1 -i "${srcdir}"/"${patch}"
        ;;
    esac
  done
}

build() {
  arch-meson 'kmod' 'build' \
    -Dbuild-tests=true \
    -Dmanpages=true \
    -Dopenssl=enabled \
    -Dxz=enabled \
    -Dzlib=enabled \
    -Dzstd=enabled

  meson compile -C build
}

check() {
  # As of kmod v20, the test suite needs to build some kernel modules, and thus
  # needs headers available in order to run. We depend on linux-headers, but
  # this is really only to try and make sure that *some* useable tree of kernel
  # headers exist. The first useable tree we find is good enough, as these
  # modules will never be loaded by tests.

  # Holo: set KDIR=any to allow the usage of any installed kernel header, and not
  # only the one for the currently running kernel

  KDIR=any meson test -C 'build'
}

package() {
  meson install -C 'build' --destdir "$pkgdir"

  # extra directories
  install -dm0755 "${pkgdir}"/{etc,usr/lib}/{depmod,modprobe}.d

  # install depmod.d file for search/ dir
  install -Dm0644 "${srcdir}/depmod-search.conf" "${pkgdir}/usr/lib/depmod.d/search.conf"

  # hook
  install -Dm0644 "${srcdir}/depmod.hook" "${pkgdir}/usr/share/libalpm/hooks/60-depmod.hook"
  install -Dm0755 "${srcdir}/depmod.script" "${pkgdir}/usr/share/libalpm/scripts/depmod"
}
