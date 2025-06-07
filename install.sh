#!/bin/bash

echo "🔧 Installation des dépendances et compilation du projet..."

# Vérification de l'OS et installation des paquets nécessaires
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "📦 Détection de macOS..."
    brew install sdl2 sdl2_ttf
elif [[ -f /etc/debian_version ]]; then
    echo "📦 Détection de Debian/Ubuntu..."
    sudo apt update && sudo apt install -y libsdl2-dev libsdl2-ttf-dev wget unzip
elif [[ -f /etc/redhat-release ]]; then
    echo "📦 Détection de Fedora/CentOS..."
    sudo dnf install -y SDL2-devel SDL2_ttf-devel wget unzip
elif [[ "$(uname)" == "FreeBSD" ]]; then
    echo "📦 Détection de FreeBSD..."
    sudo pkg install -y sdl2 sdl2_ttf wget unzip
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "📦 Détection de Windows (MSYS2)..."
    pacman -S --noconfirm mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf wget unzip
elif [[ -f /etc/arch-release ]]; then
    echo "📦 Détection de Arch Linux..."
    sudo pacman -Sy --noconfirm sdl2 sdl2_ttf wget unzip
else
    echo "❌ OS non supporté. Installez SDL2 et SDL2_ttf manuellement."
    exit 1
fi

# Création du dossier assets s'il n'existe pas
mkdir -p assets

# Téléchargement et installation de la police Cascadia Code
echo "🔠 Installation de la police Cascadia Code..."
FONT_URL="https://github.com/microsoft/cascadia-code/releases/download/v2407.24/CascadiaCode-2407.24.zip"
wget -O assets/CascadiaCode.zip "$FONT_URL"
unzip -o assets/CascadiaCode.zip -d assets/
mv assets/ttf/CascadiaCode.ttf assets/CascadiaCode.ttf
rm -rf assets/CascadiaCode.zip assets/ttf
rm -rf assets/otf
rm -rf assets/woff2


# Compilation du projet
echo "⚙️ Compilation du projet..."
gcc -o SlashEditor main.c handle.c window.c -lSDL2 -lSDL2_ttf

echo "✅ Installation terminée ! Lancez le programme avec :"
echo "   ./SlashEditor"
