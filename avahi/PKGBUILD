# Maintainer: Jan Alexander Steffens (heftig) <jan.steffens@gmail.com>
# Contributor: Gaetan Bisson <bisson@archlinux.org>
# Contributor: Douglas Soares de Andrade <douglas@archlinux.org>

# Holo: Ship a modified config file to disable mDNS publishing
# This allows better coexistence with sd-resolved while providing
# enough mDNS browsing support for CUPS remote printing to work.
# sd-resolved: Used by steamos devkit (mDNS publishing)
# avahi: mDNS browsing (finding network printers for CUPS)
pkgname=avahi
pkgver=0.8+r194+g3f79789c
pkgrel=3.2
epoch=1
pkgdesc="Service Discovery for Linux using mDNS/DNS-SD (compatible with Bonjour)"
url="https://github.com/avahi/avahi"
license=(LGPL)
arch=(x86_64)
depends=(
  dbus
  expat
  gdbm
  glib2
  libcap
  libdaemon
)
makedepends=(
  doxygen
  git
  glib2-devel
  gobject-introspection
  graphviz
  gtk3
  libevent
  python-dbus
  python-gobject
  qt5-base
  xmltoman
)
optdepends=(
  'gtk3: avahi-discover, avahi-discover-standalone, bshell, bssh, bvnc'
  'libevent: libevent bindings'
  'nss-mdns: NSS support for mDNS'
  'python-dbus: avahi-bookmarks, avahi-discover'
  'python-gobject: avahi-bookmarks, avahi-discover'
  'python-twisted: avahi-bookmarks'
  'qt5-base: qt5 bindings'
)
provides=(
  libavahi-{client,common,core,glib,gobject,libevent,qt5,ui-gtk3}.so
  libdns_sd.so
)
backup=(
  etc/avahi/{hosts,avahi-daemon.conf,avahi-{autoip,dnsconf}d.action}
  usr/lib/avahi/service-types.db
)
_commit=3f79789c484518f82c36ff59c0f45abe7e6580a2  # master
source=(
  "git+https://github.com/avahi/avahi#commit=$_commit"
  0001-HACK-Install-fixes.patch
  0002-disable-publishing-by-default.patch
  9c4214146738146e454f098264690e8e884c39bd.context-trimmed.patch
)
b2sums=(SKIP
        'a15b00c05cce3b6a1479d88b1393cd955a80c669fed03be5f624a8e8701f22fe327bbd42f7563a532ae8ebc39408f3aedfc982c42a2b6141ccc22af96f16293c'
        'c815c1c394df7f098d2d68651c6b8837d7b8519db782df89212b7865ea4d99533f623f376529c1234becaae6dada5574089541011ba1443ad12855d6a2fe2c2f'
        '2794f19b8d55d94ad86eabb09f951a68333e308ad72b8ea72314af7e80c0b2af7e5b760d16bf8c7268eb2d3679a8833be6c3e9c28d7b4a5f1ac30f395b39d357')

pkgver() {
  cd avahi
  git describe --tags | sed 's/^v//;s/[^-]*-g/r&/;s/-/+/g'
}

prepare() {
  cd avahi

  # https://bugs.archlinux.org/task/47822
  git apply -3 ../0001-HACK-Install-fixes.patch

  # Holo: disable publishing by default (handled by sd-resolved on Holo)
  patch -p1 < ../0002-disable-publishing-by-default.patch

  # Holo: disable enable-wide-area to mitigate CVE-2024-52615 and
  # CVE-2024-52616, and because it's been disabled by default due to other
  # problems.  Patch taken from upstream, with slightly trimmed context to apply
  # cleanly, as previous patches modify the same lines.
  patch -p1 < ../9c4214146738146e454f098264690e8e884c39bd.context-trimmed.patch

  NOCONFIGURE=1 ./autogen.sh
}

build() {
  local configure_options=(
    --prefix=/usr
    --sysconfdir=/etc
    --localstatedir=/var
    --sbindir=/usr/bin
    --runstatedir=/run
    --disable-mono
    --enable-compat-libdns_sd
    --with-autoipd-group=avahi
    --with-autoipd-user=avahi
    --with-avahi-priv-access-group=network
    --with-distro=archlinux
    --with-systemdsystemunitdir=/usr/lib/systemd/system
    with_dbus_sys=/usr/share/dbus-1/system.d
  )

  cd avahi

  ./configure "${configure_options[@]}"
  sed -i -e 's/ -shared / -Wl,-O1,--as-needed\0/g' libtool
  make
}

package() {
  depends+=(libdbus-1.so)

  cd avahi
  make DESTDIR="$pkgdir" install

  echo 'u avahi - "Avahi mDNS/DNS-SD daemon"' |
    install -Dm644 /dev/stdin "$pkgdir/usr/lib/sysusers.d/$pkgname.conf"
}

# vim:set sw=2 sts=-1 et:
