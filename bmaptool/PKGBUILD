# Maintainer: Holo Team

pkgname=bmaptool
replaces=('bmap-tools')
pkgver=3.9.0
pkgrel=1
pkgdesc="Tool optimized for copying largely sparse files using information from a block map (bmap) file"
arch=('any')
url='https://github.com/yoctoproject/bmaptool'
license=('GPL-2.0-only')
depends=('python>=3.14' 'python<3.15')
makedepends=('python-build' 'python-installer' 'python-hatchling')
checkdepends=('python-gpgme' 'python-six' 'zip' 'unzip')
source=("${pkgname}-${pkgver}.tar.gz::${url}/archive/refs/tags/v${pkgver}.tar.gz")
b2sums=('cffa465124f1b3c9738a797d3f4eda6252b546476fee6b8c2fabffba71a4da50d8249c74097049e5337a866a08a6d4849eb08fe9c0d909cf105d389f776c5a64')

build() {
  cd "${pkgname}-${pkgver}"
  python -m build --wheel --no-isolation
}

check() {
  cd "${pkgname}-${pkgver}"
  python -m venv --system-site-packages test-env
  test-env/bin/python -m installer dist/*.whl
  PATH="${PWD}/test-env/bin:${PATH}" test-env/bin/python -P -m unittest -v
}

package() {
  cd "${pkgname}-${pkgver}"
  python -m installer --destdir="$pkgdir" dist/*.whl
  install -Dm644 -t "$pkgdir/usr/share/man/man1" docs/man1/bmaptool.1
}

# vim:set ts=2 sw=2 et:
