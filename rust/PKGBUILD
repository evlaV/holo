# Maintainer: Johannes Löthberg <johannes@kyriasis.com>
# Maintainer: Jan Alexander Steffens (heftig) <heftig@archlinux.org>
# Contributor: Alexander F Rødseth <xyproto@archlinux.org>
# Contributor: Daniel Micay <danielmicay@gmail.com>
# Contributor: userwithuid <userwithuid@gmail.com>

pkgbase=rust
pkgname=(
  rust
  lib32-rust-libs
  rust-musl
  rust-aarch64-gnu
  rust-aarch64-musl
  rust-wasm
  rust-src
)
epoch=1
pkgver=1.84.1
pkgrel=1
pkgdesc="Systems programming language focused on safety, speed and concurrency"
url=https://www.rust-lang.org/
arch=(x86_64)
license=("Apache-2.0 OR MIT")
options=(
  !emptydirs
  !lto
)
depends=(
  bash
  curl
  gcc
  gcc-libs
  glibc
  libssh2
  llvm-libs
  openssl
  zlib
)
makedepends=(
  aarch64-linux-gnu-gcc
  aarch64-linux-gnu-glibc
  clang
  cmake
  lib32-gcc-libs
  lib32-glibc
  libffi
  lld
  llvm
  musl
  musl-aarch64
  ninja
  perl
  python
  rust
  wasi-libc
  wasm-component-ld
)
checkdepends=(
  gdb
  procps-ng
)
source=(
  "https://static.rust-lang.org/dist/rustc-$pkgver-src.tar.gz"{,.asc}
  0001-bootstrap-Change-libexec-dir.patch
  0002-bootstrap-Change-bash-completion-dir.patch
  0003-compiler-Change-LLVM-targets.patch
  0004-compiler-Use-wasm-ld-for-wasm-targets.patch
  0005-compiler-Use-aarch64-linux-gnu-gcc-to-link-aarch64-t.patch
)
b2sums=('c0952f44632813e6ddfd36754bbbc498511cd80a1dd613f41f027b363fbd97bdf825013262438fac56bbc88c53ec557103119b4d60e7be5cd58b3ec51f1fc2c2'
        'SKIP'
        '27b0083fd9996846783055dc03186a023ab4e1ec782eef8cebbf5d0dae5b3b0e38ec20254d960aa9a05fbe7944d30e8bea0593c22a3ddae276ca149a9af692d9'
        '9fcedd009d8c90e2d49e72e080b978fbd2feb14bd50dc2a8c679e781667d62a43ad1f2fccf20b30442024b6f2b9acf47f2246a5cff62f18d2002f4cf940b0b45'
        '17aa45250ac4842e4cdc9e37e4e805ee064ea06b3c81d2ce549d0bc4c51cbd9f96efd16de7683e02efe4542553277a340e9edb27b4f6e48ba7f162bc4e4ca5d2'
        'b50e77529edc7640e2e08a434aa48591b5b809b35e61db026010e28b6c4caf61a780131500a5b0f9339d2a98177de7adb13d7589a0b2f084304d059c4de112ee'
        '6805ff5c678bfeb1a951875de902b49b2f0ded812b0bf9fa7368a375888985b8d6e3c74cda4d9b830706f7da1ec4fa239f9799a013409b4cd79e4b5c065c643b')
validpgpkeys=(
  108F66205EAEB0AAA8DD5E1C85AB96E6FA1BE5FE  # Rust Language (Tag and Release Signing Key) <rust-key@rust-lang.org>
)

# Make sure the duplication in rust-wasm is found
COMPRESSZST+=(--long)

prepare() {
  cd rustc-$pkgver-src

  # Patch bootstrap so that rust-analyzer-proc-macro-srv
  # is in /usr/lib instead of /usr/libexec
  patch -Np1 -i ../0001-bootstrap-Change-libexec-dir.patch

  # Put bash completions where they belong
  patch -Np1 -i ../0002-bootstrap-Change-bash-completion-dir.patch

  # Use our *-pc-linux-gnu targets, making LTO with clang simpler
  patch -Np1 -i ../0003-compiler-Change-LLVM-targets.patch

  # Use our wasm-ld
  patch -Np1 -i ../0004-compiler-Use-wasm-ld-for-wasm-targets.patch

  # Use our aarch64-linux-gnu-gcc
  patch -Np1 -i ../0005-compiler-Use-aarch64-linux-gnu-gcc-to-link-aarch64-t.patch

  cat >config.toml <<END
# see src/bootstrap/defaults/
profile = "dist"

# see src/bootstrap/src/utils/change_tracker.rs
change-id = 131075

[llvm]
download-ci-llvm = false
link-shared = true

[build]
target = [
  "x86_64-unknown-linux-gnu",
  "i686-unknown-linux-gnu",
  "x86_64-unknown-linux-musl",
  "aarch64-unknown-linux-gnu",
  "aarch64-unknown-linux-musl",
  "wasm32-unknown-unknown",
  "wasm32-wasip1",
  "wasm32-wasip1-threads",
  "wasm32-wasip2",
]
cargo = "/usr/bin/cargo"
rustc = "/usr/bin/rustc"
rustfmt = "/usr/bin/rustfmt"
locked-deps = true
vendor = true
tools = [
  "cargo",
  "clippy",
  "rustdoc",
  "rustfmt",
  "rust-analyzer-proc-macro-srv",
  "analysis",
  "src",
]
sanitizers = true
profiler = true

# Generating docs fails with the wasm32-* targets
docs = false

[install]
prefix = "/usr"

[rust]
codegen-units-std = 1
debuginfo-level = 1
debuginfo-level-std = 2
channel = "stable"
description = "Arch Linux $pkgbase $epoch:$pkgver-$pkgrel"
rpath = false
frame-pointers = true
lld = false
use-lld = "external"
llvm-bitcode-linker = false
deny-warnings = false
backtrace-on-ice = true
remap-debuginfo = false
jemalloc = true

[dist]
compression-formats = ["gz"]
compression-profile = "fast"

[target.x86_64-unknown-linux-gnu]
cc = "/usr/bin/gcc"
cxx = "/usr/bin/g++"
ar = "/usr/bin/gcc-ar"
ranlib = "/usr/bin/gcc-ranlib"
llvm-config = "/usr/bin/llvm-config"

[target.i686-unknown-linux-gnu]
cc = "/usr/bin/gcc"
cxx = "/usr/bin/g++"
ar = "/usr/bin/gcc-ar"
ranlib = "/usr/bin/gcc-ranlib"

[target.x86_64-unknown-linux-musl]
cc = "/usr/bin/musl-gcc"
cxx = "/usr/bin/g++"
ar = "/usr/bin/gcc-ar"
ranlib = "/usr/bin/gcc-ranlib"
sanitizers = false
musl-root = "/usr/lib/musl"

[target.aarch64-unknown-linux-gnu]
cc = "/usr/bin/aarch64-linux-gnu-gcc"
cxx = "/usr/bin/aarch64-linux-gnu-g++"
ar = "/usr/bin/aarch64-linux-gnu-gcc-ar"
ranlib = "/usr/bin/aarch64-linux-gnu-gcc-ranlib"
linker = "/usr/bin/aarch64-linux-gnu-gcc"
default-linker = "aarch64-linux-gnu-gcc"

[target.aarch64-unknown-linux-musl]
cc = "/usr/aarch64-linux-musl/bin/musl-gcc"
cxx = "/usr/bin/aarch64-linux-gnu-g++"
ar = "/usr/bin/aarch64-linux-gnu-gcc-ar"
ranlib = "/usr/bin/aarch64-linux-gnu-gcc-ranlib"
linker = "/usr/bin/aarch64-linux-gnu-gcc"
default-linker = "aarch64-linux-gnu-gcc"
sanitizers = false
musl-root = "/usr/aarch64-linux-musl/lib/musl"

[target.wasm32-unknown-unknown]
cc = "/usr/bin/clang"
cxx = "/usr/bin/clang++"
ar = "/usr/bin/llvm-ar"
ranlib = "/usr/bin/llvm-ranlib"
linker = "/usr/bin/wasm-ld"
default-linker = "wasm-ld"
sanitizers = false
profiler = false

[target.wasm32-wasip1]
cc = "/usr/bin/clang"
cxx = "/usr/bin/clang++"
ar = "/usr/bin/llvm-ar"
ranlib = "/usr/bin/llvm-ranlib"
linker = "/usr/bin/wasm-ld"
default-linker = "wasm-ld"
sanitizers = false
profiler = false
wasi-root = "/usr/share/wasi-sysroot"

[target.wasm32-wasip1-threads]
cc = "/usr/bin/clang"
cxx = "/usr/bin/clang++"
ar = "/usr/bin/llvm-ar"
ranlib = "/usr/bin/llvm-ranlib"
linker = "/usr/bin/wasm-ld"
default-linker = "wasm-ld"
sanitizers = false
profiler = false
wasi-root = "/usr/share/wasi-sysroot"

[target.wasm32-wasip2]
cc = "/usr/bin/clang"
cxx = "/usr/bin/clang++"
ar = "/usr/bin/llvm-ar"
ranlib = "/usr/bin/llvm-ranlib"
linker = "/usr/bin/wasm-ld"
default-linker = "wasm-ld"
sanitizers = false
profiler = false
wasi-root = "/usr/share/wasi-sysroot"
END
}

_pick() {
  local p="$1" f d; shift
  for f; do
    d="$srcdir/$p/${f#$pkgdir/}"
    mkdir -p "$(dirname "$d")"
    mv "$f" "$d"
    rmdir -p --ignore-fail-on-non-empty "$(dirname "$f")"
  done
}

build() {
  cd rustc-$pkgver-src

  export RUST_BACKTRACE=1
  unset CFLAGS CXXFLAGS LDFLAGS

  DESTDIR="$srcdir/dest-rust" python ./x.py install -j "$(nproc)"

  cd ../dest-rust

  # delete unnecessary files, e.g. files only used for the uninstall script
  rm -v usr/lib/rustlib/{components,install.log,rust-installer-version,uninstall.sh}
  rm -v usr/lib/rustlib/manifest-*

  # licenses for main rust package
  local ldir="usr/share/licenses/rust" f d
  mkdir -p "$ldir"
  for f in usr/share/doc/*/{COPYRIGHT,LICENSE}*; do
    d="$(dirname "$f")"
    case $f in
      */LICENSE-APACHE) rm -v "$f" ;;
      *) mv -v "$f" "$ldir/${f##*/}.${d##*/}" ;;
    esac
    rmdir -p --ignore-fail-on-non-empty "$d"
  done

  # rustbuild always installs copies of the shared libraries to /usr/lib,
  # overwrite them with symlinks to the per-architecture versions
  mkdir -pv usr/lib32
  ln -srvft usr/lib   usr/lib/rustlib/x86_64-unknown-linux-gnu/lib/*.so
  ln -srvft usr/lib32 usr/lib/rustlib/i686-unknown-linux-gnu/lib/*.so

  _pick dest-i686 usr/lib/rustlib/i686-unknown-linux-gnu usr/lib32
  _pick dest-musl usr/lib/rustlib/x86_64-unknown-linux-musl
  _pick dest-aarch64-gnu usr/lib/rustlib/aarch64-unknown-linux-gnu
  _pick dest-aarch64-musl usr/lib/rustlib/aarch64-unknown-linux-musl
  _pick dest-wasm usr/lib/rustlib/wasm32-*
  _pick dest-src  usr/lib/rustlib/src
}

package_rust() {
  optdepends=(
    'gdb: rust-gdb script'
    'lldb: rust-lldb script'
  )
  provides=(
    cargo
    rustfmt
  )
  conflicts=(
    cargo
    'rust-docs<1:1.56.1-3'
    rustfmt
  )
  replaces=(
    cargo
    cargo-tree
    'rust-docs<1:1.56.1-3'
    rustfmt
  )

  cp -a dest-rust/* "$pkgdir"
}

package_lib32-rust-libs() {
  pkgdesc="32-bit target and libraries for Rust"
  depends=(
    lib32-gcc-libs
    lib32-glibc
    rust
  )
  provides=(lib32-rust)
  conflicts=(lib32-rust)
  replaces=(lib32-rust)

  cp -a dest-i686/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

package_rust-musl() {
  pkgdesc="Musl target for Rust"
  depends=(rust)

  cp -a dest-musl/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

package_rust-aarch64-gnu() {
  pkgdesc="AArch64 GNU target for Rust"
  depends=(
    aarch64-linux-gnu-gcc
    aarch64-linux-gnu-glibc
    rust
  )

  cp -a dest-aarch64-gnu/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

package_rust-aarch64-musl() {
  pkgdesc="AArch64 Musl target for Rust"
  depends=(
    aarch64-linux-gnu-gcc
    rust
  )

  cp -a dest-aarch64-musl/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

package_rust-wasm() {
  pkgdesc="WebAssembly targets for Rust"
  depends=(
    lld
    rust
    wasm-component-ld
  )

  cp -a dest-wasm/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

package_rust-src() {
  pkgdesc="Source code for the Rust standard library"
  depends=(rust)

  cp -a dest-src/* "$pkgdir"

  install -Dt "$pkgdir/usr/share/licenses/$pkgname" -m644 \
    rustc-$pkgver-src/{COPYRIGHT,LICENSE-MIT}
}

# vim:set ts=2 sw=2 et:
