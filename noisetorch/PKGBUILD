# Maintainer: holo-team

pkgname=noisetorch
pkgver=0.12.2.r47.g6d895f3
pkgrel=3
_commit=6d895f35d32a6a7dd5f472f596ccfb6cfeac5c08  # Latest tested version
pkgdesc="RNNoise LADSPA noise suppression filter for pipewire & pulseaudio"
url=https://github.com/noisetorch/NoiseTorch
arch=(x86_64 aarch64)
license=(GPL3)
makedepends=(git gcc make)
source=("noisetorch::git+https://github.com/noisetorch/NoiseTorch.git#commit=${_commit}"
        'README.md')
sha512sums=('cac256311734482ebb9329a1a670811387e8ab6b76296f95c057f8613bf505fe08b2f95a46953c137c6eb656af289cafb38e632fe19fe7418806a5f52dd7f7c0'
            '0307006381f5603d1e1db3e327b475f9bd9599cf7f1b41f747abc1e49b509502a4790ac1686826c5e1902273d72312f414275046fbd9b2032603bd16543cb118')

pkgver() {
    cd "$pkgname"
    git describe --long --tags --abbrev=7 | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g'
}

prepare ()
{
    cd "$pkgname"
    git submodule update --init --recursive
}

build ()
{
    # NOTE: we only build the ladspa ELF DSO from this project
    cd "$pkgname"
    cd c/ladspa
    make
}

package ()
{
    shopt -s nullglob
    local so=

    mkdir -p "$pkgdir"/usr/lib/ladspa

    for so in "$srcdir/$pkgname/c/ladspa/"*.so
    do
        cp -av "$so" "$pkgdir"/usr/lib/ladspa/
    done

    mkdir -p "$pkgdir"/usr/share/noisetorch
    cp -avL README.md "$pkgdir"/usr/share/noisetorch/
    cp -av "$srcdir"/"$pkgname"/LICENSE "$pkgdir"/usr/share/noisetorch/
}
