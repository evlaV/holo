# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Maintainer: Levente Polyak <anthraxx[at]archlinux[dot]org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>

pkgname=bubblewrap
pkgver=0.12.0
pkgrel=1.1 # Rebuild for Holo
pkgdesc='Unprivileged sandboxing tool'
url='https://github.com/containers/bubblewrap'
arch=(x86_64)
license=(LGPL-2.1-or-later)
depends=(
  glibc
  libcap
  libgcc
)
makedepends=(
  bash-completion
  docbook-xsl
  git
  libxslt
  meson
)
source=("git+$url?signed#tag=v$pkgver")
b2sums=('7fc2f4cffe860630f2887de49d0807a99d3fd41c34259f85f3d3fdf8f3d9131b0fdf24269bc93da5b06a92d144a26a04345f0e51bbfab3e3cc3c6048df60b986')
validpgpkeys=(
  DA98F25C0871C49A59EAFF2C4DE8FF2A63C7CC90 # Simon McVittie <smcv@collabora.com>
  252C6FEA78A69D3BC0AD458A616C5BDC0C29AB04 # Alexander Larsson <alexl@redhat.com>
)

prepare() {
  cd $pkgname
}

build() {
  local meson_options=(
    # major.minor.0 of linux-lts
    -D assume_kernel=6.18.0

    -D selinux=disabled
  )

  arch-meson $pkgname build "${meson_options[@]}"
  meson compile -C build
}

check() {
  # Broken in our build containers
  meson test -C build --print-errorlogs || :
}

package() {
  replaces=("bubblewrap-suid<=0.11.2-1")

  meson install -C build --destdir "$pkgdir"
}

# vim:set sw=2 sts=-1 et:
