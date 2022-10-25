# Maintainer (upstream): emersion <contact emersion fr>
# Maintainer (ugly holo vendoring of meson stuff sorry): John Schoenick <johns@valvesoftware.com>
pkgname=drm_info
pkgver=2.4.0
pkgrel=1
license=('MIT')
pkgdesc='Small utility to dump info about DRM devices'
makedepends=("meson" "git" "scdoc")
depends=("libdrm" "json-c" "pciutils")
arch=("x86_64")
url='https://gitlab.freedesktop.org/emersion/drm_info'
source=("${pkgname}::git+https://gitlab.freedesktop.org/emersion/drm_info.git#tag=v${pkgver}"
        # Meson subproject
        "git+https://gitlab.freedesktop.org/mesa/drm.git")
sha1sums=('SKIP'
          'SKIP')

prepare() {
  # meson subprojects
  cd "$srcdir/$pkgname"

  # Clone manually, set URL to the real upstream so meson doesn't get upset, then ask `meson subprojects update` to
  # ensure the right commit/state.
  #
  # Why isn't there a way to vendor git deps without half-tricking meson?
  git clone "$srcdir/drm" subprojects/libdrm
  ( cd subprojects/libdrm && git remote set-url origin https://gitlab.freedesktop.org/mesa/drm.git )
  meson subprojects update libdrm

  # We do not need to vendor the json-c subproject, as it wont be used so long as the system one is present.
  # Once system libdrm is new enough, we can skip vendoring libdrm here.
}

# pkgver() {
#   cd "${srcdir}/${pkgname}"
#   git describe --long --tags --abbrev=8 | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g'
# }

build() {
  cd "${srcdir}/${pkgname}"

  arch-meson build/
  ninja -C build/
}

package() {
  cd "${srcdir}/${pkgname}"

  DESTDIR="$pkgdir/" ninja -C build/ install
}
