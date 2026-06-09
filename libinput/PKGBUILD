# Maintainer: Andreas Radke <andyrtr@archlinux.org>

pkgname=libinput
pkgver=1.28.1
pkgrel=1.1 # Holo: Fix CVE-2026-50292
pkgdesc="Input device management and event handling library"
url="https://gitlab.freedesktop.org/libinput/libinput"
arch=(x86_64)
license=(MIT)
depends=('mtdev' 'libevdev' 'libwacom' 'systemd-libs' 'glibc')
# upstream doesn't recommend building docs
makedepends=('gtk4' 'meson' 'wayland-protocols' 'check') # 'doxygen' 'graphviz' 'python-sphinx' 'python-recommonmark'
checkdepends=('python-pytest')
optdepends=('gtk4: libinput debug-gui'
            'python-pyudev: libinput measure'
            'python-libevdev: libinput measure'
            'python-yaml: used by various tools')
source=(https://gitlab.freedesktop.org/libinput/libinput/-/archive/$pkgver/$pkgname-$pkgver.tar.bz2
        0001-CVE-2026-50292.patch
        0002-CVE-2026-50292.patch
        0003-CVE-2026-50292.patch)
sha256sums=('19e5337ec10fdf920c8d1f4ece63cd7d1c12279ee26e347e30e98e2942d9e1aa'
            SKIP
            SKIP
            SKIP)
#validpgpkeys=('3C2C43D9447D5938EF4551EBE23B7E70B467F0BF') # Peter Hutterer (Who-T) <office@who-t.net>

# Holo: Apply all patches
prepare() {
  cd "${pkgname}-${pkgver}"

  for patch in "${source[@]}"
  do
    case $patch in
      *.patch)
        echo "# Applying ${patch}"
        patch -p1 -i "${srcdir}"/"${patch}"
        ;;
    esac
  done
}

build() {
  arch-meson $pkgname-$pkgver build \
    -D udev-dir=/usr/lib/udev \
    -D documentation=false

  # Print config
  meson configure build

  meson compile -C build
}

check() {
  meson test -C build --print-errorlogs
}

package() {
  meson install -C build --destdir "$pkgdir"

  install -Dvm644 $pkgname-$pkgver/COPYING \
    "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}
