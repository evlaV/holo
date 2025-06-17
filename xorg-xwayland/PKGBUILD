# Maintainer: AndyRTR <andyrtr@archlinux.org>
# This PKGBUILD reverts a couple of commits to maintain compatibility with how
# gamescope + steam + steamwebhelper expect xwayland to work. These commits can
# be restored once xorg-xwayland, gamescope, steam, and steamwebhelper work
# together properly again.

pkgname=xorg-xwayland
pkgver=24.1.7
pkgrel=1.1 # Add seamless boot fixes
arch=('x86_64')
license=(
    LicenseRef-Adobe-Display-PostScript
    BSD-3-Clause
    LicenseRef-DEC-3-Clause
    HPND
    LicenseRef-HPND-sell-MIT-disclaimer-xserver
    HPND-sell-variant
    ICU
    ISC
    MIT
    MIT-open-group
    NTP
    SGI-B-2.0
    SMLNJ
    X11
    X11-distribute-modifications-variant
)
groups=('xorg')
url="https://xorg.freedesktop.org"
pkgdesc="run X clients under wayland"
depends=('nettle' 'libepoxy' 'libxfont2' 'pixman'
         'xorg-server-common' 'libxcvt' 'mesa'
         'libglvnd' 'libxau' 'wayland' 'libdrm' 'libtirpc'
         'libei' 'libxshmfence' 'libdecor' 'glibc')
makedepends=('meson' 'xorgproto' 'xtrans' 'libxkbfile' 'dbus'
             'xorg-font-util' 'wayland-protocols' 'mesa-libgl'
             'systemd')
# These two reverts are necessary to fix:
# 0001) a black screen between the boot splash and steam start up animation
# 0002) getting stuck on the boot splash forever if 0001 is applied
# The details are given in
# https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1390
# https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1649
source=(https://xorg.freedesktop.org/archive/individual/xserver/xwayland-$pkgver.tar.xz{,.sig}
        "0001-Revert-xwayland-Restrict-allow-commit-to-the-window-.patch"
        "0002-Revert-xwayland-present-Check-allow_commits-in-xwl_p.patch"
)
sha512sums=('b5c5d39619743bff328c178a7496f04e17b527d3d7d6f6f54b0d2804fed54dbae16b76eb8f3921ca2557fa50b85601e40f8a2c809dc3c1e896cc1c662f91e013'
            'SKIP'
            'cc214c44d0c4c06627a4359a6a6d07349643c901cee555187314d9bd846e78c4238184adad732bb4bcf241b2db822785b96b3a035be175a766b9511d899f6999'
            '99f0935a4efc26c0f992063cd03c121a68f9972fbf6938c40585e9f2b20d15068e722e85ac945511af3cfa206132ca980aaae36a3734f65c2829327ea471ec4f'
)
provides=('xorg-server-xwayland')
conflicts=('xorg-server-xwayland')
replaces=('xorg-server-xwayland')
#validpgpkeys=('B09FAF35BE914521980951145A81AF8E6ADBB200') # "Michel Daenzer <michel@daenzer.net>"
validpgpkeys=('67DC86F2623FC5FD4BB5225D14706DBE1E4B4540') # "Olivier Fourdan <fourdan@xfce.org>"
validpgpkeys+=('3C2C43D9447D5938EF4551EBE23B7E70B467F0BF') # Peter Hutterer (Who-T) <office@who-t.net>

prepare () {
  local patch=
  cd xwayland-$pkgver

  for patch in "${source[@]}"
  do
    case $patch in
      *.patch)
        echo "Applying $patch"
        patch -p1 < ../$patch
        ;;
    esac
  done
}

build() {
  arch-meson xwayland-$pkgver build \
    -D ipv6=true \
    -D xvfb=false \
    -D xdmcp=false \
    -D xcsecurity=true \
    -D dri3=true \
    -D glamor=true \
    -D libdecor=true \
    -D xkb_dir=/usr/share/X11/xkb \
    -D xkb_output_dir=/var/lib/xkb

  # Print config
  meson configure build
  ninja -C build
}

package() {

  DESTDIR="${pkgdir}" ninja -C build install
  # xorg-server-common file /usr/lib/xorg/protocol.txt
  rm "${pkgdir}"/usr/lib/xorg/protocol.txt
  rmdir "${pkgdir}"/usr/lib/xorg
  rm "${pkgdir}"/usr/share/man/man1/Xserver.1

  # license
  install -m644 -Dt "${pkgdir}/usr/share/licenses/${pkgname}" xwayland-$pkgver/COPYING
}
