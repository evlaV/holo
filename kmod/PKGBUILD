# Maintainer: Dave Reisner <dreisner@archlinux.org>

pkgname=kmod
pkgver=33
# SteamOS use /usr/lib/steamos/modules
pkgrel=3.2
pkgdesc="Linux kernel module management tools and library"
arch=('x86_64')
url='https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git'
license=('LGPL-2.1-or-later' 'GPL-2.0-or-later')
depends=('glibc' 'zlib' 'openssl' 'xz' 'zstd')
makedepends=('git' 'scdoc')
checkdepends=('linux-headers' 'libelf')
options=('strip')
provides=('libkmod.so')
validpgpkeys=('EAB33C9690013C733916AC839BA2A5A630CBEA53')  # Lucas DeMarchi
source=("git+https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git#tag=v${pkgver}?signed"
        'depmod-search.conf'
        'depmod.hook'
        'depmod.script')
sha256sums=('f5795fe50a747609d70f764244e645cd946074e70a7e51de0f82bd2e4d0612c8'
            '1a92bfeae870f61ce814577e69d2a147a9c0caf6aed1131243e4179241fcc4a8'
            '4c96f1fda1b4893d03e0ce2c377442bb39e30cd76a85103ede4e93b7d1d5701d'
            '18661aa40c25580f04d2ac3f32e54c2997c0994d1c829905537b413a9d291ac6')

prepare() {
  cd "${pkgname}"

  touch libkmod/docs/gtk-doc.make
  autoreconf --force --install --symlink
}

build() {
  cd "${pkgname}"

  ./configure \
    --sysconfdir='/etc' \
    --with-xz \
    --with-zlib \
    --with-zstd \
    --with-openssl

  make
}

check() {
  # As of kmod v20, the test suite needs to build some kernel modules, and thus
  # needs headers available in order to run. We depend on linux-headers, but
  # this is really only to try and make sure that *some* useable tree of kernel
  # headers exist. The first useable tree we find is good enough, as these
  # modules will never be loaded by tests.

  local kdirs=(/usr/lib/modules/*/build/Makefile)
  if [[ ! -f ${kdirs[0]} ]]; then
    printf '==> Unable to find kernel headers to build modules for tests\n' >&2
    return 1
  fi

  local kver kdir="${kdirs[0]%/Makefile}"
  IFS=/ read _ _ _ kver _ <<<"${kdir}"

  make -C "${pkgname}" check KDIR="${kdir}" KVER="${kver}"
}

package() {
  make -C "${pkgname}" DESTDIR="${pkgdir}" install

  # extra directories
  install -dm0755 "${pkgdir}"/{etc,usr/lib}/{depmod,modprobe}.d

  # install depmod.d file for search/ dir
  install -Dm0644 "${srcdir}/depmod-search.conf" "${pkgdir}/usr/lib/depmod.d/search.conf"

  # hook
  install -Dm0644 "${srcdir}/depmod.hook" "${pkgdir}/usr/share/libalpm/hooks/60-depmod.hook"
  install -Dm0755 "${srcdir}/depmod.script" "${pkgdir}/usr/share/libalpm/scripts/depmod"
}

# vim: ft=sh syn=sh et
