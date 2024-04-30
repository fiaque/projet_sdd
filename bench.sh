#!/bin/bash

# Variables d'environnement
# format de la commande time pour n'avoir que le temps en secondes
export TIMEFORMAT=%R
# format des nombres pour ne pas avoir de soucis aves les nombres à
# virgule dans awk
export LC_NUMERIC="C"

# commande à exécuter
commande="sleep 1"
# nombre de répétitions de la commande
nombre_iterations=5

temps_total=0.0

for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
echo "Temps moyen : ${temps_moyen}"
