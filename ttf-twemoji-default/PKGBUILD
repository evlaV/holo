# Maintainer: Joe Baker < JoeBlakeB at protonmail dot com >
# Maintainer: Joshua Ashton <joshua@froggi.es>

pkgname=ttf-twemoji-default
pkgver=13.1.0
pkgrel=2.4
_fedrel=1.fc35
pkgdesc="Twitter Emoji for everyone."
url="https://github.com/twitter/twemoji"
arch=(any)
license=('CCPL' 'MIT' 'Apache')
makedepends=('python-fonttools' 'python>=3.13' 'python<3.14')
depends=('fontconfig')
provides=('emoji-font' 'ttf-twemoji')
conflicts=('ttf-twemoji')
source=("https://kojipkgs.fedoraproject.org/packages/twitter-twemoji-fonts/${pkgver}/${_fedrel}/noarch/twitter-twemoji-fonts-${pkgver}-${_fedrel}.noarch.rpm"
        "75-twemoji.conf"
        "twemoji-glyph-remove.patch")
sha256sums=('2730d76b7939be467571dd0f10d4f5b1f8396e96743173750e27d45ac7ab2f07'
            'a77a7775557efc1c17781c0fc35a0f7ec5ccd58f233573f8875032fb8575680e'
            '748a877491ab1d1c94bc911456c716e8490c321a452c808ef063fddbaf0db4c0')

prepare() {
    ttx -o twemoji.ttx usr/share/fonts/twemoji/Twemoji.ttf
    patch twemoji.ttx twemoji-glyph-remove.patch
    ttx -o twemoji.ttf twemoji.ttx
}

package() {
    install -Dm644 twemoji.ttf "${pkgdir}/usr/share/fonts/twemoji/twemoji.ttf"
    install -Dm644 -t "${pkgdir}/usr/share/fontconfig/conf.avail" 75-twemoji.conf
    install -Dm644 -t "${pkgdir}/usr/share/licenses/${pkgname}" \
      usr/share/licenses/twitter-twemoji-fonts/LICENSE{,-{BUILD,GRAPHICS}}

    # Enable it by default! That's why this package has the -default suffix. ✨
    # We make a symlink at the pkg's /etc/fonts/conf.d/75-twemoji.conf to where it will be
    # after it's installed, so: /usr/share/fontconfig/conf.avail/75-twemoji.conf
    # This will be maintained after install.
    mkdir -p "${pkgdir}/etc/fonts/conf.d"
    ln -sf /usr/share/fontconfig/conf.avail/75-twemoji.conf "${pkgdir}/etc/fonts/conf.d/75-twemoji.conf"
}
