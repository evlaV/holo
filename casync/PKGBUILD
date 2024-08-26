# Maintainer: John Schoenick <johns@valvesoftware.com>
# Contributor: Collabora Ltd <gael.portay@collabora.com>

pkgname=casync
_commit=99559cd
# Should match what pkgver() generates below
pkgver=2.r227.g99559cd
pkgrel=4.2
pkgdesc="Content-Addressable Data Synchronization Tool"
arch=(x86 x86_64)
url="https://github.com/systemd/casync"
license=('LGPL')
depends=('acl' 'fuse2' 'libcurl.so' 'libudev.so' 'openssl' 'xz' 'zlib' 'zstd')
makedepends=('git' 'meson' 'python-sphinx'
  'python>=3.11'
  'python<3.12'
)
optdepends=()
checkdepends=('rsync')
source=("$pkgname::git+$url#commit=$_commit"
        '0001-shell-completion-support-for-options.patch'
        '0002-shell-completion-handle-completion-per-command.patch'
        '0003-shell-completion-add-helper-__casync_get_arg_n.patch'
        '0001-Fix-usage-for-list-and-mtree-commands.patch'
        '0002-man-reword-list-command-section.patch'
        '0003-man-fix-top-level-path-in-stat-command-section.patch'
        '0005-Fix-usage-and-reword-digest-command.patch'
        '0001-casync-tool-fix-missing-return-statement-with-log_er.patch'
        '0002-casync-tool-return-log_error_errno-whenever-it-is-po.patch'
        '0001-tool-fix-push-pull-usage-error.patch'
        '0001-Copy-TAKE_PTR-from-systemd.patch'
        '0002-Rewrite-casync-http-to-use-curl-multi.patch'
        '0001-Add-download-progress.patch'
        '0002-Add-seeding-progress.patch'
        '0003-Force-display-of-extract-stats.patch'
        '0001-casync-http-make-the-use-of-.netrc-optional.patch'
        '0001-caencoder-remove-sys-mount.h-to-fix-build-against-gl.patch')

sha256sums=('SKIP'
            'b7000251a5bd6072a6cc9f359cc63556a17f4bc3a513af96870f60371ffa3c28'
            'e6eaeff97a38588c40849cbfe8f0409f16cffc8157e90c5088d3609dbd2ad42b'
            'bf86f7480cdf566476d14a8ab6d802fa30e22a26c99d9d5a3cb4cf3fed11a2e7'
            'f1d99ae8c0ceb58dd6d0049401f6a47df8713b735a38ce49eea8fd45ed1729c1'
            'bd254aa810bff20a7e613ea2fe676e0953fa2e8a03a97d72423218590e7af6ef'
            'eada9ffb0de9a212658171c3df1bfc6ecc5250b0c343db7d97b4a194da580a98'
            '5e67658278a7d11097e14d7bd6b1647f2e43733c31a206b87ebe036a6fe6b18f'
            '612270575e7ead9b91c0f7695a2666f87c3ac5b9255386e80260cde22d1e3012'
            'e00c35aa3ee506cf59d6a128af6b3f2be3fc6f21f355bf1dc4ad9b8bba8ccc30'
            '478901f6dc3a033a4def8174c969b1ab34f476cf975bc3ea8753f496747cc2d3'
            '7223f2b23c839a555ba431cfcf7f423196a32321908d7353ab2291525463f4ca'
            '57d64511c0353ae4253fefcf20dacc8544d565d008204909da9cb07b39033151'
            '7eb294a530b626d3ef1e71dae463d6886eeec8effa3864b20be14700bffae67b'
            '799462b39676675196d4bf99565fe51f3ea4f705d197004faaf2a3e8bbedaad5'
            '957ae0a2715a6b22cda16ddec29d037438d4a4772767d7d072418d47ce0871a8'
            '0a580459c2732e8de14cdb2081845062a3c3dc4446f739fb64695c3ab77f83a5'
            '89d0ceda9f5dbb3cbd83ae1db651e573d9ba8fee355d50c88887ca5939d1660c')

pkgver() {
  cd "$pkgname"
  ( set -o pipefail
    git describe --tags 2>/dev/null | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g' ||
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
  )
}

prepare() {
  cd "$srcdir/$pkgname"
  echo "Patch for SteamOS..."
  patch -p1 -i "$srcdir/0001-shell-completion-support-for-options.patch"
  patch -p1 -i "$srcdir/0002-shell-completion-handle-completion-per-command.patch"
  patch -p1 -i "$srcdir/0003-shell-completion-add-helper-__casync_get_arg_n.patch"
  patch -p1 -i "$srcdir/0001-Fix-usage-for-list-and-mtree-commands.patch"
  patch -p1 -i "$srcdir/0002-man-reword-list-command-section.patch"
  patch -p1 -i "$srcdir/0003-man-fix-top-level-path-in-stat-command-section.patch"
  patch -p1 -i "$srcdir/0005-Fix-usage-and-reword-digest-command.patch"
  patch -p1 -i "$srcdir/0001-casync-tool-fix-missing-return-statement-with-log_er.patch"
  patch -p1 -i "$srcdir/0002-casync-tool-return-log_error_errno-whenever-it-is-po.patch"
  patch -p1 -i "$srcdir/0001-tool-fix-push-pull-usage-error.patch"
  patch -p1 -i "$srcdir/0001-Copy-TAKE_PTR-from-systemd.patch"
  patch -p1 -i "$srcdir/0002-Rewrite-casync-http-to-use-curl-multi.patch"
  patch -p1 -i "$srcdir/0001-Add-download-progress.patch"
  patch -p1 -i "$srcdir/0002-Add-seeding-progress.patch"
  patch -p1 -i "$srcdir/0003-Force-display-of-extract-stats.patch"
  patch -p1 -i "$srcdir/0001-casync-http-make-the-use-of-.netrc-optional.patch"
  patch -p1 -i "$srcdir/0001-caencoder-remove-sys-mount.h-to-fix-build-against-gl.patch"
}

build() {
  cd "$srcdir/$pkgname"
  arch-meson build/ -Dselinux=false
  ninja -C build/
}

#check() {
#  cd "$srcdir/$pkgname/build"
#  meson test
#}

package() {
  cd "$srcdir/$pkgname"
  DESTDIR="$pkgdir/" ninja -C build/ install
}
