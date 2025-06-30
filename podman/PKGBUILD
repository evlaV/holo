# Maintainer: Morten Linderud <foxboron@archlinux.org>
# Maintainer: David Runge <dvzrv@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Maintainer (Holo): Alberto Garcia <berto@igalia.com>

pkgbase=podman
pkgname=podman
pkgver=5.3.2
pkgrel=1.2 # Holo: build only podman and not podman-docker. Fix CVE-2025-6032
pkgdesc='Tool and library for running OCI-based containers in pods'
arch=(x86_64)
url='https://github.com/containers/podman'
license=(Apache-2.0)
makedepends=(
  apparmor
  btrfs-progs
  catatonit
  git
  go
  go-md2man
  gpgme
  libseccomp
  man-db
  shadow
  systemd
)
# https://github.com/containers/podman/issues/13297
options=(!lto)
source=(
  "git+$url?signed#tag=v$pkgver"
  "fix-cve-2025-6032.patch"
)
# See the release-keys repository
# https://github.com/containers/release-keys
validpgpkeys=(
  B7DBDCA456F7335E91F1C25CD3624C551D0515C4  # Matthew Heon <mheon@redhat.com>
  7CE1E6F8C90CB53E7E4D8F2D502E08DB0BBF8EEE  # Ashley Cui <acui@redhat.com>
  9E33DD8704CC03E2DEB84D9A1C1EDD7CC7C3A0DD  # Lokesh Mandvekar <lsm5@redhat.com>
)
sha256sums=('73399e271ea86c7a7de68222a6ff0fd4f0d9d60c7ceb45df2685ca4d86f2f53d'
            '1b4f7d231a357b9ca324ecfae77d72c03b6cc7cafdb30cb8384b4510fdc2d64c')

prepare() {
  cd $pkgname
  # Holo: Patch for CVE-2025-6032. Fixed upstream in v5.5.2: https://github.com/advisories/GHSA-65gg-3w2w-hr4h
  patch -p1 < "${srcdir}/fix-cve-2025-6032.patch"
}

build() {
  export CGO_CPPFLAGS="${CPPFLAGS}"
  export CGO_CFLAGS="${CFLAGS}"
  export CGO_CXXFLAGS="${CXXFLAGS}"
  export CGO_LDFLAGS="${LDFLAGS}"
  export GOFLAGS="-buildmode=pie"
  export GOPATH="${srcdir}"

  make -j1 EXTRA_LDFLAGS='-compressdwarf=false -linkmode=external' PREFIX=/usr -C $pkgbase
  make docker-docs -C $pkgbase
}

package_podman() {
  depends=(
    catatonit
    conmon
    containers-common
    oci-runtime
    gcc-libs
    glibc
    iptables
    gpgme libgpgme.so
    libseccomp libseccomp.so
    passt
    shadow
  )
  optdepends=(
    'apparmor: for AppArmor support'
    'btrfs-progs: support btrfs backend devices'
    'cni-plugins: for an alternative container-network-stack implementation'
    'fuse-overlayfs: for storage driver in rootless environment'
    'slirp4netns: for alternative rootless network support'
    'podman-compose: for docker-compose compatibility'
    'podman-docker: for Docker-compatible CLI'
  )

  make install install.completions DESTDIR="$pkgdir" PREFIX=/usr LIBEXECDIR=/usr/lib -C $pkgbase

  # Holo: remove podman-remote, it's quite big and we don't need it
  rm -f "$pkgdir/usr/bin/podman-remote"
  rm -f "$pkgdir/usr/share/bash-completion/completions/podman-remote"
  rm -f "$pkgdir/usr/share/fish/vendor_completions.d/podman-remote.fish"
  rm -f "$pkgdir/usr/share/man/man1/podman-remote.1"
  rm -f "$pkgdir/usr/share/zsh/site-functions/_podman-remote"
}

package_podman-docker() {
  pkgdesc='Emulate Docker CLI using podman'
  depends=(
    podman
    sh
  )
  conflicts=(docker)
  provides=(docker)

  make -j1 install.docker-full DESTDIR="$pkgdir" PREFIX=/usr -C $pkgbase
}
