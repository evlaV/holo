# Maintainer: Morten Linderud <foxboron@archlinux.org>
# Maintainer: David Runge <dvzrv@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Maintainer (Holo): Alberto Garcia <berto@igalia.com>

pkgbase=podman
pkgname=podman
pkgver=6.0.2
pkgrel=2.1 # Holo: build only podman and not podman-docker. Remove podman-remote to reduce its size
pkgdesc='A tool for managing OCI containers and pods.'
arch=(x86_64)
url='https://github.com/podman-container-tools/podman'
license=(Apache-2.0)
makedepends=(
  apparmor
  btrfs-progs
  catatonit
  containers-common
  git
  go
  go-md2man
  gpgme
  libseccomp
  man-db
  shadow
  sqlite
  systemd
)
# https://github.com/containers/podman/issues/13297
options=(!lto)
source=(
  "git+$url?signed#tag=v$pkgver"
)
# See the release-keys repository
# https://github.com/containers/release-keys
validpgpkeys=(
  B7DBDCA456F7335E91F1C25CD3624C551D0515C4  # Matthew Heon <mheon@redhat.com>
  7CE1E6F8C90CB53E7E4D8F2D502E08DB0BBF8EEE  # Ashley Cui <acui@redhat.com>
  9E33DD8704CC03E2DEB84D9A1C1EDD7CC7C3A0DD  # Lokesh Mandvekar <lsm5@redhat.com>
)
sha512sums=('52ed49139a317ff73b2cb03cdf16293b87b44fee0f48a0ca355846a7b6dccb76ac2b64dc1e4f5246c388277df07552dbda27db40ab042cb68f1d9a49d51ae7ba')
b2sums=('0ce0c7f04e44e9cc9a222cb4018e742a574b69874a5fab534a60c7060fa0a13938f858e84ae834bbb15cabc22d75305beffc4ab9898b487cd1b1e250311718d7')

build() {
  export CGO_CPPFLAGS="${CPPFLAGS}"
  export CGO_CFLAGS="${CFLAGS}"
  export CGO_CXXFLAGS="${CXXFLAGS}"
  export CGO_LDFLAGS="${LDFLAGS}"
  export GOFLAGS="-buildmode=pie"
  export GOPATH="${srcdir}"

  make EXTRA_LDFLAGS='-linkmode=external' PREFIX=/usr -C $pkgbase
  make docker-docs -C $pkgbase
}

check() {
  local container_libs_version="$(</usr/share/containers/container-libs.version)"
  local project_container_libs_version="$(sed --regexp-extended --quiet 's|.*go.podman.io/common v(.*)|\1|p' "$pkgbase/go.mod")"

  printf '%s %s (container-libs %s) - system container-libs %s\n' "$pkgbase" "$pkgver" "${project_container_libs_version%.*}" "${container_libs_version%.*}"

  if (( $(vercmp "${container_libs_version%.*}" "${project_container_libs_version%.*}") != 0 )); then
    printf '%s %s requires container-libs/common in version %s but we have version %s\n' "$pkgbase" "$pkgver" "${project_container_libs_version%.*}" "${container_libs_version%.*}"
    exit 1
  fi
}

package_podman() {
  depends=(
    catatonit
    conmon
    containers-common
    oci-runtime
    glibc
    nftables
    gpgme libgpgme.so
    libgcc
    libseccomp libseccomp.so
    passt
    shadow
    sqlite
  )
  optdepends=(
    'apparmor: for AppArmor support'
    'btrfs-progs: support btrfs backend devices'
    'fuse-overlayfs: for deprecated storage driver in rootless environment'
    'podlet:  Generate Podman Quadlet files from a Podman command, compose file, or existing object'
    'podman-compose: for docker-compose compatibility'
    'podman-desktop: GUI and tray to manage Podman containers (and Kubernetes pods)'
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

  make install.docker-full DESTDIR="$pkgdir" PREFIX=/usr -C $pkgbase
}
