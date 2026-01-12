# 🎮 Awale - Jeu de Stratégie Traditionnel

![Langage](https://img.shields.io/badge/language-C-orange.svg)
![Library](https://img.shields.io/badge/library-SDL3-green.svg)

Une implémentation numérique du célèbre jeu d'Awalé, développée en langage **C** avec la bibliothèque **SDL3**.
Ce projet a été conçu pour offrir une expérience fluide, avec une interface graphique soignée et une gestion complète des règles traditionnelles.

## ✨ Fonctionnalités
- 🎨 Interface graphique utilisant **SDL3**, **SDL3_image** et **SDL3_ttf**.
- 🔊 Effets sonores immersifs.
- 🏆 Gestion complète des scores et des captures de graines.
- 🏁 Menu principal et écran de fin de partie.

---

## 🚀 Installation & Test
Si vous souhaitez simplement jouer, vous pouvez télécharger l'installeur Windows sur ma page **https://alfa-narcisse.itch.io/awale**.

---

## 🛠️ Compilation (Développeurs)

### Prérequis
- Un compilateur C (ex: **GCC** via MSYS64 sur Windows).
- La bibliothèque **SDL3** (incluant les modules `image` et `ttf`).

### Structure du projet
Pour que le projet compile avec la configuration actuelle, respectez l'arborescence suivante :
```text
.
├── assets/         # Images, sons et polices
├── build/            # Exécutable généré
├── include/        # Fichiers .h
├── src/            # Fichiers .c
├── SDL3/          # Dossier de la bibliothèque (à installer)
└── README.md
