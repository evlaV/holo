# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Maintainer (Holo): David Redondo <kde@david-redondo.de>

pkgname=discover
pkgver=6.4.3
_dirver=$(echo $pkgver | cut -d. -f1-3)
pkgrel=1.5 # Holo: Enable Holo backend, hide system updates setting, fix losing progress for tasks
           # NOTE: (was called SteamOS backend)
pkgdesc='KDE and Plasma resources management GUI'
arch=(x86_64)
url='https://apps.kde.org/discover/'
license=(LGPL-2.0-or-later)
depends=(appstream-qt
         archlinux-appstream-data
         attica
         discount
         gcc-libs
         glib2
         glibc
         kcmutils
         kconfig
         kcoreaddons
         kcrash
         kdbusaddons
         ki18n
         kiconthemes
         kidletime
         kio
         kirigami
         kirigami-addons
         kjobwidgets
         knewstuff
         knotifications
         kservice
         kstatusnotifieritem
         kuserfeedback
         kwidgetsaddons
         kwindowsystem
         purpose
         qcoro
         qqc2-desktop-style
         qt6-base
         qt6-declarative
         qt6-webview)
makedepends=(extra-cmake-modules
             flatpak
             fwupd
             packagekit-qt6)
optdepends=('flatpak: Flatpak packages support'
            'fwupd: firmware update support'
            'packagekit-qt6: to manage packages from Arch Linux repositories (not recommended, use at your own risk)')
groups=(plasma)
source=(https://download.kde.org/stable/plasma/$_dirver/$pkgname-$pkgver.tar.xz{,.sig}
        'https://invent.kde.org/plasma/discover/-/commit/1a527660d.patch'  # Drop after 6.5
        'https://invent.kde.org/plasma/discover/-/commit/79df60ca9.patch'  # Drop after 6.5
        'https://invent.kde.org/plasma/discover/-/commit/b48fe3ba2.patch'  # Drop after 6.5
        'https://invent.kde.org/plasma/discover/-/commit/0d4f43d9b.patch'  # Drop after 6.5
        'https://invent.kde.org/plasma/discover/-/commit/7c999205b.patch'  # Drop after 6.6
        0001-libdiscover-backends-SteamOS-rename-to-Holo.patch             # Holo: rename discover backend (ETA 6.6.0)
        0002-po-libdiscover-move-translations-to-Holo-from-SteamO.patch    # Holo: rename discover backend (update translations) (DROP at 6.6)
        0003-libdiscover-HoloBackend-Make-the-OS-name-track-etc-o.patch)   # Holo: display OS name from /etc/os-release (ETA 6.6.0)
sha256sums=('c2dd8238aaa8c801a12c6f29d70f24467bad59209c5fc8fae97cbbbac45dde10'
            'SKIP'
            '241ecac39011026c5fd8088dd3157faee7146e561c184c1f2cdd997b06b3743e'
            '26326beb9a41b5a2b08d3468e8df8ecb681ba1d09946755aaa9934775aaff84f'
            '1f7746cd2266e274f0bd4ba812fa129c7810c71a584c96574a1f85f24071a29b'
            'af69d31acb0e8458ce7e003bc58301d5b38d708b7d32d3d611769ef5b5a84c82'
            'e44fe97955cd73a89937f530748f921d75f8a5718f5f56f1bfc2c39a1dde4c9e'
            '275caa6193d3041f2b4ab5b9dbf8a2e0b5994249949e0c5de69c8a511e9d6117'
            'f7a8c10e26bd043c7585f5fa5eaf876c0b0fa75f0593b8ce7f7b98ec0794a1c4'
            '821d6e7c54379ced419ace46d4e90a016e737e3ca577d1946b03d458d3e92165')
validpgpkeys=('E0A3EB202F8E57528E13E72FD7574483BB57B18D'  # Jonathan Esk-Riddell <jr@jriddell.org>
              '0AAC775BB6437A8D9AF7A3ACFE0784117FBCE11D'  # Bhushan Shah <bshah@kde.org>
              'D07BD8662C56CB291B316EB2F5675605C74E02CF'  # David Edmundson <davidedmundson@kde.org>
              '1FA881591C26B276D7A5518EEAAF29B42A678C20') # Marco Martin <notmart@gmail.com>

prepare() {
  local patch=
  local file=
  cd "$srcdir"/"$pkgname"-"$pkgver"

  # Cherry-pick 3 upstream commits to hide the setting governing when
  # to apply system updates. This can be dropped when the package is
  # rebased on a future version > 6.5.4 (the first two commits are in
  # 6.5.0, the third one hasn't been released yet as of this writing).
  # 0d4f43d9b is a patch fix for discover losing progress for a task
  # in some cases, and it can be dropped when package is rebased on
  # future version 6.4.6 or higher.
  for patch in "${source[@]}"
  do
    case $patch in
      *.patch)
        file=$(get_filename "$patch")
        echo "Applying $patch"
        if ! patch -p1 < "$srcdir"/"$file"
        then
          echo "ERROR: Patch $patch failed"
          exit 1
        fi
        ;;
    esac
  done
}

build() {
  # Holo: HoloBackend should be enabled. It's disabled by default.
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_LIBEXECDIR=lib \
    -DBUILD_HoloBackend=ON \
    -DBUILD_TESTING=OFF
  cmake --build build
}

package() {
  depends+=(atomupd-daemon) # the steamos updater talks to it via dbus
  DESTDIR="$pkgdir" cmake --install build
}
