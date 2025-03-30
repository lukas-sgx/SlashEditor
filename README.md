# 🚀 SlashEditor  

📝 Un éditeur de texte simple et rapide en **C** avec **SDL2**.  



## 📦 Installation  

### 1️⃣ Prérequis
Avant de commencer, assurez-vous que les dépendances suivantes sont installées sur votre système :

#### 📌 Linux (Debian/Ubuntu)
```bash
sudo apt update && sudo apt install -y libsdl2-dev libsdl2-ttf-dev gcc make
```

#### 📌 macOS (via Homebrew)
```bash
brew install sdl2 sdl2_ttf
```

#### 📌 Windows (via MSYS2)
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf
```



### 2️⃣ Cloner le dépôt  
```bash
git clone https://github.com/lukas-sgx/SlashEditor.git
cd SlashEditor
```

### 3️⃣ Installer les dépendances et compiler  
```bash
chmod +x install.sh
./install.sh

gcc -o SlashEditor main.c handle.c window.c -lSDL2 -lSDL2_ttf
./SlashEditor
```



## 🎮 Commandes  

| 🎯 **Raccourcis clavier** | 📝 **Action** |
|---------------------------|--------------|
| `Ctrl + O`               | Ouvrir un fichier |
| `Ctrl + S`               | Sauvegarder le fichier |
| `Ctrl + Q`               | Quitter l'éditeur |



## 🛠️ Technologies utilisées  

- ✅ **Langage** : C  
- ✅ **Bibliothèques** : SDL2, SDL_ttf, stdio, string  



## 📌 Fonctionnalités prévues  

- ✨ **Coloration syntaxique**  
- ✨ **Mode sombre & thèmes personnalisés**  
- ✨ **Gestion de plusieurs fichiers (onglets)**  
- ✨ **Terminal intégré**  



## 👨‍💻 Contributeurs  

💡 **Développeur principal** : [Lukas](https://github.com/lukas-sgx)  

## ⚖️ Licence  

📜 **Licence MIT** - Utilisation libre et open-source !  