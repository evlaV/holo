# Maintainer: Morten Linderud <foxboron@archlinux.org>
# Contributor: Bartłomiej Piotrowski <bpiotrowski@archlinux.org>
# Contributor: Thomas Bächler <thomas@archlinux.org>
# Contributor: loqs

pkgname=wpa_supplicant
pkgver=2.12
pkgrel=1.3
epoch=2
pkgdesc='A utility providing key negotiation for WPA wireless networks'
url='https://w1.fi/wpa_supplicant/'
arch=(x86_64)
license=(BSD-3-Clause)
depends=(
  glibc
  libdbus
  libnl
  openssl
  pcsclite
  readline
)
makedepends=(
  docbook-sgml
  docbook-utils
  git
  perl-sgmls
)
source=(
  "git+https://git.w1.fi/hostap.git?signed#tag=hostap_${pkgver//./_}"
  wpa_supplicant_config

  # More permissive TLS fallback
  0001-Enable-TLSv1.0-by-default.patch

  # https://salsa.debian.org/debian/wpa/-/commit/13e1d28e4f987a220c546df94df86bb9b2371874
  0002-Disable-Werror-for-eapol_test.patch

  # https://lists.infradead.org/pipermail/hostap/2022-May/040511.html
  # https://bugs.archlinux.org/task/76474
  0003-Allow-legacy-renegotiation-to-fix-PEAP-issues-with-s.patch

  # Unit improvements from Ubuntu
  0004-Tweak-D-Bus-systemd-service-activation-configuration.patch
  0005-Add-IgnoreOnIsolate-yes-to-keep-wpa-supplicant-runni.patch

  # More unit improvements from Debian
  0006-Add-reload-support-to-the-systemd-unit-files.patch

  # https://lists.infradead.org/pipermail/hostap/2022-January/040178.html
  0007-nl80211-add-extra-ies-only-if-allowed-by-driver.patch

  # Fix authentication regressions with Broadcom brcmfmac fullmac devices.
  0008-Revert-Mark-authorization-completed-on-driver-indica.patch

  # Holo: https://gitlab.steamos.cloud/holo-team/tasks/-/work_items/1457
  # These patches are backported from upstream and will be available in next wpa_supplicant release
  # https://git.w1.fi/cgit/hostap/commit/?id=20e1762ee4355995e3e471cc4a1e18e021c73f92
  # https://git.w1.fi/cgit/hostap/commit/?id=ab3200b10628bbae50abb56edb7c48334452d6e5
  0001-wpa_supplicant-Avoid-redundant-rescan-when-6-GHz-was.patch
  0002-wpa_supplicant-Don-t-force-rescan-for-restricted-sca.patch

  # Holo: https://gitlab.steamos.cloud/holo-team/tasks/-/work_items/2284
  # https://lists.infradead.org/pipermail/hostap/2026-August/045488.html
  0001-SAE-Also-treat-UNSPECIFIED_FAILURE-as-a-password-mis.patch

)
b2sums=('632b255467f1c7b52fccaf217ff471a89a59943b74bef3536f7b5eb6146527dc9e86c67e8c40162a3809f14a97dc94c3a339bc77d356c9ef16cfcf41fcd00208'
        '5ae5c1ece9a4b81db5048c84ecff7427bc474a6db0a4a1c8cf43a0e89e15932df8494dbea39b571026f77daca98cc71418440f17d1885b87eb8d5266d8c4dc7b'
        'ec738735c4e820f87082b8bd86f07c458cf9c8137734f65b01cbc88ead66c90d7c362a88465cedaff1eacad3e6d43bc97d846e3d7c22132038b026c28c70a63a'
        'df0cebf38b8c9c03055db2d5a60d21b64b277165d7238173ef21e7bdbffca883795b9fa517bdfd4ab1eb9d288d1237f339d9e6bdb92d679e662eefe98843e42c'
        '28ebf66b30a421830470ff191b0ff6ca10a91acc66d36024ccfce0e024f17cd05f136564982cc0fb6b99ec4d791d1e501b6dd7c4130f3cae10a5f8e7e6a350b1'
        '7175e7aab682370aef1b3358eaa839dcb009e12940aa2b9949c8c3254406341433e84af09d09ad670bf41f5201d979af02095c87a368b76465a952b1be9de049'
        '6472d571f18c3ee718315888b9c756c4579a4b411e8c6994002f9a79fb0a36fbebe8b3d419af0f9ea881dd1bc439d03dbe3c6d6661e670f16575197c31f0bd7a'
        'c1ce2e8d6f42cbc8181aeb2bdc19d4a22bff804c18f6e505d8315a294c67c936e90135046812ec37765be3d0f433e31554604deb1d7b160549d7e3284610a22b'
        'c70aa659f2e5e5cd59d7f5006eda115f780a6bdcb3e006505c9dde560c590d596da368795ee42991d4735b9c8e55eb9412a58dfc17239f518c5ecdb013347cce'
        '72742bba49ea105419d510f64c3d728d672efa4a91612bfd7d22d5c46d98e0d496ae7713f971074442621f6e87d5623fa33675b6b329278422f50b3a4afdbf1b'
        '0747e1b8a4d75252ef44dba58e8fa1c9caffe21fa1379f6cca1588c955fb840c9bc69683d8118e89b06e0ab652639fdf3fff4b6b1030af7402507d0ba3a56efe'
        '22be75bbf9a695e30f9ab76d0a35dfd1a848d26cb2a9085d73aaab1813aee0346b7023a09f7c3377b83266bc2ef658a6fd36aced941f84f44c131fc61a1b12ab'
        '8a578b2cee42f849d4808f37d1c393e7f8f38ced9eb68a181b79c0f43d1ab2ab4c878cfbea7d44a75ef8183a6d2feb8e56503819234fca1dff2fb50b2c901bd9')
validpgpkeys=(
  EC4AA0A991A5F2464582D52D2B6EF432EFC895FA # Jouni Malinen <j@w1.fi>
)

prepare() {
  cd hostap

  local src
  for src in "${source[@]}"; do
    [[ $src = *.patch ]] || continue
    echo "Applying patch $src..."
    git apply -3 < "../$src"
  done

  cp ../wpa_supplicant_config $pkgname/.config
}

_make() {
  local make_options=(
    BINDIR=/usr/bin
    LIBDIR=/usr/lib
    "$@"
  )

  make "${make_options[@]}"
}

build() {
  cd hostap/$pkgname

  _make
  _make eapol_test
  _make -C doc/docbook man
}

package() {
  cd hostap/$pkgname

  _make DESTDIR="$pkgdir" install

  install -Dm755 eapol_test "$pkgdir/usr/bin/eapol_test"

  install -dm755 "$pkgdir/etc/wpa_supplicant"
  install -Dm644 wpa_supplicant.conf -t "$pkgdir/usr/share/doc/wpa_supplicant"

  install -Dm644 dbus/fi.w1.wpa_supplicant1.service \
    -t "$pkgdir/usr/share/dbus-1/system-services"

  install -Dm644 dbus/dbus-wpa_supplicant.conf \
    "$pkgdir/usr/share/dbus-1/system.d/wpa_supplicant.conf"

  install -Dm644 doc/docbook/*.5 -t "$pkgdir/usr/share/man/man5"
  install -Dm644 doc/docbook/*.8 -t "$pkgdir/usr/share/man/man8"
  rm "$pkgdir"/usr/share/man/man8/wpa_{priv,gui}.8

  install -Dm644 systemd/*.service -t "$pkgdir/usr/lib/systemd/system"

  install -Dm644 ../README "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}

# vim:set sw=2 sts=-1 et:
