# Maintainer: AndyRTR <andyrtr@archlinux.org>
# This PKGBUILD reverts a couple of commits to maintain compatibility with how
# gamescope + steam + steamwebhelper expect xwayland to work. These commits can
# be restored once xorg-xwayland, gamescope, steam, and steamwebhelper work
# together properly again.

pkgname=xorg-xwayland
pkgver=24.1.14
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
        "0003-LibEi-keysyms.patch"  # allows Steam OSK CJK to work, not upstream yet, requires patched libei.Track at https://gitlab.freedesktop.org/libinput/libei/-/merge_requests/355
)
sha512sums=('0c09214bf5478697430db3f403ba6fc5b669faab4428a902ce9e148ea5dae630798da03f2977ab937486a07224fa2e73d146e3f51fff8abe00d2dd78d5a05bf1'
            'SKIP'
            '0460c52e705bfa8e48a4332ec7c1f85f317b61aab471aa58487786e83ec5943aa96d8ad8d5f37f04c809e4b314d9612d46c8b6abc3ba3f9b337b68e71baea122'
            '0ff4c0628d284e4fed31ade64153871b38607458884d002719ad4030661e159ad72cbc5a3e4b0c0478ab0dd8f4eaceb6dcfb97301b575fc5679836b16f5ada9e'
            '1b7d1e09e963fc1c47974565a0516e7de948a7f24dbd3fd011e237c4e8d1ee198a3c85979a2b40a5e2c6cd6286a793cd36f94ae4bed72aec9ac418cf843e6b85')
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
