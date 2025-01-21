# PDE_Pricer

Ce projet est un **pricer** d'options financières développé en C++. Il utilise la méthode des **différences finies explicites** pour résoudre des équations aux dérivées partielles (EDP) afin de calculer les prix de diverses options, notamment des options vanilla et exotiques.

## Fonctionnalités
- **Options vanilla :**
  - Call européen
  - Put européen
- **Options exotiques :**
  - Call Asset-Or-Nothing
  - Call barrière knock-out (KO)

## Compilation et exécution
### Compilation
Pour compiler le pricer, exécutez la commande suivante dans un terminal :
```bash
g++ -std=c++11 Pricer.cpp src/Payoff.cpp src/Option.cpp src/EDP.cpp src/MDF.cpp -o Pricer
```
### Compilation
Pour exécuter le pricer, utilisez la commande :
```bash
./Pricer
```
Les résultats sont affichés dans le terminal et exportés sous forme de fichiers CSV dans le dossier output/. Ces fichiers contiennent les résultats pour chaque pas de temps et d’espace.

## Visualisation des résultats
Le projet inclut des scripts Python permettant de visualiser graphiquement les résultats produits par le pricer. Pour exécuter ces scripts, utilisez les commandes suivantes :
- **Call européen :**
```bash
python python_scripts/Call.py
```
- **Put européen :**
```bash
python python_scripts/Put.py
```
- **Call Asset-Or-Nothing :**
```bash
python python_scripts/AssetOrNothing.py
```
- **Call barrière KO :**
```bash
python python_scripts/Barrier_CallKO.py
```

## Structure du projet
- `src/` : Contient les fichiers sources du pricer en C++.
- `output/` : Contient les fichiers CSV générés après l’exécution.
- `python_scripts/` : Contient les scripts Python pour visualiser les résultats.
- `Pricer.cpp` : Fichier principal pour exécuter le pricer.

## Pré-requis
- **C++ compiler :** `g++` ou équivalent (supportant `-std=c++11`).
- **Python3.x :** Avec les bibliothèques suivantes installées :
  - `matplotlib`
  - `numpy`
  - `pandas`
Vous pouvez installer ces bibliothèques via :
```bash
pip install matplotlib numpy pandas
```

## Auteurs
Ce projet à été fait par Samuel Alvarez, Simon Duong et Lucas Leproult, étudiants à l'ENSAE.
