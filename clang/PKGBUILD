# Maintainer: Evangelos Foutras <evangelos@foutrelis.com>
# Contributor: Jan "heftig" Steffens <jan.steffens@gmail.com>

pkgbase=clang
pkgname=(clang clang-libs)
pkgver=16.0.6
pkgrel=2.1
pkgdesc="C language family frontend for LLVM"
arch=('x86_64')
url="https://clang.llvm.org/"
license=('custom:Apache 2.0 with LLVM Exception')
makedepends=('llvm' 'cmake' 'ninja' 'python-sphinx' 'python-recommonmark')
options=('!debug')
_source_base=https://github.com/llvm/llvm-project/releases/download/llvmorg-$pkgver
source=($_source_base/$pkgbase-$pkgver.src.tar.xz{,.sig}
        $_source_base/clang-tools-extra-$pkgver.src.tar.xz{,.sig}
        $_source_base/llvm-$pkgver.src.tar.xz{,.sig}
        $_source_base/cmake-$pkgver.src.tar.xz{,.sig}
        $_source_base/third-party-$pkgver.src.tar.xz{,.sig}
        clangd-handle-missing-ending-brace.patch::https://github.com/llvm/llvm-project/commit/9d1dada57741.patch
        enable-fstack-protector-strong-by-default.patch)
sha256sums=('1186b6e6eefeadd09912ed73b3729e85b59f043724bb2818a95a2ec024571840'
            'SKIP'
            '174c7844db2590b18b2a59a9ce503f8fe439edc2de2f0f625006501c99736f31'
            'SKIP'
            'e91db44d1b3bb1c33fcea9a7d1f2423b883eaa9163d3d56ca2aa6d2f0711bc29'
            'SKIP'
            '39d342a4161095d2f28fb1253e4585978ac50521117da666e2b1f6f28b62f514'
            'SKIP'
            '15f5b9aeeba938530af977d5f9205612737a091a7f0f6c8075df8723b7713f70'
            'SKIP'
            'c102e8a6a2adb0e8729865ffb8799b22bb8a9bdf0f421991880fa4393378370a'
            '45da5783f4e89e4507a351ed0ffbbe6ec240e21ff7070797a89c5ccf434ac612')
validpgpkeys=('474E22316ABF4785A88C6E8EA2C794A986419D8A'  # Tom Stellard <tstellar@redhat.com>
              'D574BD5D1D0E98895E3BF90044F2485E45D59042') # Tobias Hieta <tobias@hieta.se>

# Utilizing LLVM_DISTRIBUTION_COMPONENTS to avoid
# installing static libraries; inspired by Gentoo
_get_distribution_components() {
  local target
  ninja -t targets | grep -Po 'install-\K.*(?=-stripped:)' | while read -r target; do
    case $target in
      clang-libraries|distribution)
        continue
        ;;
      clang-tidy-headers)
        continue
        ;;
      clang|clangd|clang-*)
        ;;
      clang*|findAllSymbols)
        continue
        ;;
    esac
    echo $target
  done
}

prepare() {
  rename -v -- "-$pkgver.src" '' {cmake,third-party}-$pkgver.src
  cd "$srcdir/$pkgbase-$pkgver.src"
  mkdir build
  mv "$srcdir/clang-tools-extra-$pkgver.src" tools/extra
  patch -Np2 -i ../enable-fstack-protector-strong-by-default.patch

  # https://github.com/clangd/clangd/issues/1559
  sed 's|clang-tools-extra|clang/tools/extra|' \
    clangd-handle-missing-ending-brace.patch | patch -Np2

  # Attempt to convert script to Python 3
  2to3 -wn --no-diffs \
    tools/extra/clang-include-fixer/find-all-symbols/tool/run-find-all-symbols.py
}

build() {
  cd "$srcdir/$pkgbase-$pkgver.src/build"

  # Build only minimal debug info to reduce size
  CFLAGS=${CFLAGS/-g /-g1 }
  CXXFLAGS=${CXXFLAGS/-g /-g1 }

  local cmake_args=(
    -G Ninja
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=/usr
    -DCMAKE_INSTALL_DOCDIR=share/doc
    -DCMAKE_SKIP_RPATH=ON
    -DCLANG_DEFAULT_PIE_ON_LINUX=ON
    -DCLANG_LINK_CLANG_DYLIB=ON
    -DENABLE_LINKER_BUILD_ID=ON
    -DLLVM_BUILD_DOCS=ON
    -DLLVM_BUILD_TESTS=ON
    -DLLVM_ENABLE_RTTI=ON
    -DLLVM_ENABLE_SPHINX=ON
    -DLLVM_EXTERNAL_LIT=/usr/bin/lit
    -DLLVM_INCLUDE_DOCS=ON
    -DLLVM_LINK_LLVM_DYLIB=ON
    -DLLVM_MAIN_SRC_DIR="$srcdir/llvm-$pkgver.src"
    -DSPHINX_WARNINGS_AS_ERRORS=OFF
  )

  cmake .. "${cmake_args[@]}"
  local distribution_components=$(_get_distribution_components | paste -sd\;)
  test -n "$distribution_components"
  cmake_args+=(-DLLVM_DISTRIBUTION_COMPONENTS="$distribution_components")

  cmake .. "${cmake_args[@]}"
  ninja
}

check() {
  return 0 # Holo: disable check to speed up build
  cd "$srcdir/$pkgbase-$pkgver.src/build"
  LD_LIBRARY_PATH=$PWD/lib ninja check-clang{,-tools}
}

_python_optimize() {
  python -m compileall "$@"
  python -O -m compileall "$@"
  python -OO -m compileall "$@"
}

package_clang() {
  depends=('clang-libs' 'gcc' 'compiler-rt')
  optdepends=('openmp: OpenMP support in clang with -fopenmp'
              'python: for scan-view and git-clang-format'
              'llvm: referenced by some clang headers')
  provides=("clang-analyzer=$pkgver" "clang-tools-extra=$pkgver")
  conflicts=('clang-analyzer' 'clang-tools-extra')
  replaces=('clang-analyzer' 'clang-tools-extra')

  cd "$srcdir/$pkgbase-$pkgver.src/build"

  DESTDIR="$pkgdir" ninja install-distribution
  install -Dm644 ../LICENSE.TXT "$pkgdir/usr/share/licenses/$pkgname/LICENSE"

  # Remove documentation sources
  rm -r "$pkgdir"/usr/share/doc/clang{,-tools}/html/{_sources,.buildinfo}

  # The python and runtime libraries go into clang-libs
  mv -f "$pkgdir"/usr/lib/libclang{,-cpp}.so* "$srcdir"
  mv -f "$pkgdir"/usr/lib/{libear,libscanbuild} "$srcdir"
  mv -f "$pkgdir"/usr/libexec "$srcdir"
  mv -f "$pkgdir"/usr/bin/scan-build "$srcdir"
}

package_clang-libs() {
  depends=('llvm-libs')
  optdepends=('python: for the python bindings')

  cd "$srcdir/$pkgbase-$pkgver.src/build"

  # Move in libraries ejected at end of package_clang
  install -d "$pkgdir/usr/lib"
  install -d "$pkgdir/usr/lib/clang"
  install -d "$pkgdir/usr/bin"
  cp -a "$srcdir"/libclang{,-cpp}.so* "$pkgdir/usr/lib"
  # These three moved again below, but keeping those blocks untouched for cleaner merges with upstream monopackage.
  cp -a "$srcdir"/{libear,libscanbuild} "$pkgdir/usr/lib"
  cp -av "$srcdir"/libexec "$pkgdir"/usr/
  cp -av "$srcdir"/scan-build "$pkgdir"/usr/bin/

  # Move scanbuild-py into site-packages and install Python bindings
  local site_packages=$(python -c "import site; print(site.getsitepackages()[0])")
  install -d "$pkgdir/$site_packages"
  mv "$pkgdir"/usr/lib/{libear,libscanbuild} "$pkgdir/$site_packages/"
  cp -a ../bindings/python/clang "$pkgdir/$site_packages/"

  # Move analyzer scripts out of /usr/libexec
  mv "$pkgdir"/usr/libexec/* "$pkgdir/usr/lib/clang/"
  rmdir "$pkgdir/usr/libexec"
  sed -i 's|libexec|lib/clang|' \
    "$pkgdir/usr/bin/scan-build" \
    "$pkgdir/$site_packages/libscanbuild/analyze.py"

  # Compile Python scripts
  _python_optimize "$pkgdir/usr/share" "$pkgdir/$site_packages"

  install -Dm644 ../LICENSE.TXT "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}

# vim:set ts=2 sw=2 et:
