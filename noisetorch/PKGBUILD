# Maintainer: holo-team
pkgname=noisetorch
source=('noisetorch::git+https://github.com/noisetorch/NoiseTorch.git'
        'README.md')
pkgver=0.12.2.r47.g6d895f3

############################################################################

# Although the project is somewhat active (about a commit a month)
# there hasn't been a tagged release since 2022 - apprently they
# decided _not_ to do tagged releases anymore:
#
# From the last release announcement:
#
#   “We finally fixed the update mechanism for good. This time the
#    updater REALLY works and all future updates will be available
#    through the UI.”
#
# Since we tested main that's what we've decided to use:
_commit=6d895f35d32a6a7dd5f472f596ccfb6cfeac5c08
url=https://github.com/noisetorch/NoiseTorch/releases
############################################################################

pkgver() {
  cd "$pkgname"
  ( set -o pipefail
    git describe --tags 2>/dev/null | sed 's/^v//;s/\([^-]*-g\)/r\1/;s/-/./g' )
}


pkgrel=2
arch=(x86_64 aarch64)
pkgdesc="RNNoise LADSPA noise suppression filter for pipewire & pulseaudio"
license=(GPL3)
makedepends=(git gcc make)
sha512sums=('SKIP'
            '0307006381f5603d1e1db3e327b475f9bd9599cf7f1b41f747abc1e49b509502a4790ac1686826c5e1902273d72312f414275046fbd9b2032603bd16543cb118')

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
