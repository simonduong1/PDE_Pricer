Pour compiler le pricer, exécuter la commande suivante dans le terminal :
g++ -std=c++11 Pricer.cpp src/Payoff.cpp src/Option.cpp src/EDP.cpp src/MDF.cpp -o Pricer

L'exécution se fait ensuite via la commande : ./Pricer

En plus des résultats affichés dans le terminal, le pricer exporte l'ensemble des résultats de chaque pas de temps et d'espaces dans des fichiers CSV qui sont créés dans le dossier /output/.
Le projet inclut quatres fichiers Python permettant d'afficher les graphiques associés aux résultats qui viennent d'être calculés par le pricer. Pour les exécuter, il suffit d'exécuter les commandes suivantes :
- Pour le call : python python_scripts/Call.py
- Pour le put : python python_scripts/Put.py
- Pour le call Asset Or Nothing : python python_scripts/AssetOrNothing.py
- Pour le call barrière KO : python python_scripts/Barrier_CallKO.py