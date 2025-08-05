# Maintainer: David Runge <dvzrv@archlinux.org>
# Maintainer (Holo): Ludovico de Nittis <denittis@collabora.com>

# Holo: We backport three commits from Desync master.
# Once we'll have the upcoming Desync 0.9.7 in our repos, we can
# drop this custom PKGBUILD.

pkgname=desync
pkgver=0.9.6
pkgrel=1.2
pkgdesc="Alternative casync implementation"
arch=(x86_64)
url="https://github.com/folbricht/desync"
license=(BSD-3-Clause)
depends=(glibc)
makedepends=(go)
options=(!lto)
source=($pkgname-$pkgver.tar.gz::$url/archive/refs/tags/v$pkgver.tar.gz

        # Holo: Add the new `inspect-chunks` command and the two followup bugfixes for ChunkIDs.
        # Part of https://gitlab.steamos.cloud/holo-team/tasks/-/issues/1404
        # These patches are already merged upstream, and will be part of Desync 0.9.7
        0260be97af4d1149e32c5a0936cd14e0aeb1cc64.patch
        ec051c6880e845c355e3ed53b296524ad5e215bf.patch
        b4b3981cd074fd73977bf29fc0ffbc15e6a92773.patch
)
sha512sums=('b1f840fda8aba170c93f4b17f53595290fed1eb0a3a408e47c60214e6aabe20583c8032aec838b883d1251b31f7a819c413dca0137ab8c7d83e8de04f466d4dd'
            'efad455b39e342227b8f96e5db54f0268166cff4436b9dc9dd7b7b373247dc13f85fee5f3db8641c5d376114a92e323e904f3b6e9df830c9f23d5cfad4056e56'
            'ce4d0e62583de4282e37458c90d0c7b0f1ac5a3be6298bd4ef09782175fde2683374f818c92016b9ef6e7ab420d1c92bcea63704c54f4d626c5dc7b4a30381e5'
            'a161e8ae52dde28bb45fd8d1d51d6f2b9ae4df65a801c9f74011cb64fd4dd06bc75578981bb14c941711873ec4d91b0d1c515932d31bdd483ade9f6614c66f60')
b2sums=('eb56e5706421d2b63d9f05fe0b4d24d9c5c6eedb676c52b13563e35792198f382d48536bd0393661c20cd8fa4588949f954a7a404735ab4a078baa06e5adb2bd'
        '724c17497e61ad61fc0ea6ca1d8bafa1182c0206272a0ff94bf063ec754eb663a3cadba22f386ad1a8e9286c7da6caf663883f82f041bd76959581a6226d3c0c'
        '952dbe6abf1815b4dcea341248c8e28862f842a9007cc4bcbf5c7768988d445f3db54263edfea0460e548d91da3527f73a7a4a1b1c9303731336472a8754061a'
        '24cc18a2c3fea0e82ab7f4de9f3c0bb3f8fe9160600170ae7ba77b63763cfa82920aa2f5b518a04bfa13d8a4874822e17cbacf0544fc736000fc9b05f5870233')

prepare() {
  cd $pkgname-$pkgver
  patch -p1 -i ${srcdir}/0260be97af4d1149e32c5a0936cd14e0aeb1cc64.patch
  patch -p1 -i ${srcdir}/ec051c6880e845c355e3ed53b296524ad5e215bf.patch
  patch -p1 -i ${srcdir}/b4b3981cd074fd73977bf29fc0ffbc15e6a92773.patch
}

build() {
  export CGO_CPPFLAGS="$CPPFLAGS"
  export CGO_CFLAGS="$CFLAGS"
  export CGO_CXXFLAGS="$CXXFLAGS"
  export CGO_LDFLAGS="$LDFLAGS"
  export GOPATH="$srcdir"
  export GOFLAGS="-buildmode=pie -mod=readonly -modcacherw -buildvcs=false"

  cd $pkgname-$pkgver
  go build -ldflags "-compressdwarf=false -linkmode external" -o $pkgname ./cmd/$pkgname
}

check() {
  cd $pkgname-$pkgver
  go test ./cmd/$pkgname
}

package() {
  cd $pkgname-$pkgver
  install -vDm 755 $pkgname -t "$pkgdir/usr/bin/"
  install -vDm 644 README.md -t "$pkgdir/usr/share/doc/$pkgname/"
  install -vDm 644 LICENSE -t "$pkgdir/usr/share/licenses/$pkgname/"
}
