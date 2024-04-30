#!/bin/bash

# Variables d'environnement
# format de la commande time pour n'avoir que le temps en secondes
export TIMEFORMAT=%R
# format des nombres pour ne pas avoir de soucis aves les nombres à
# virgule dans awk
export LC_NUMERIC="C"

# commande à exécuter
commande="./timer 00014_burma.cha"
# nombre de répétitions de la commande
nombre_iterations=10

# TESTS avec listes chainées
temps_total=0.0
arg1=1
arg2=20
echo "------------ TESTS avec Liste chainée ${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"

# TESTS avec Arbre quaternaire
temps_total=0.0
arg1=3
echo "------------ TESTS avec Arbre quaternaire${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"


# TESTS 2
temps_total=0.0
arg1=2
arg2=10
echo "------------ TESTS avec Table Hashage${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
        arg2=$((${arg2}+5))
done

# fichier de NEW YORK

commande="./timer 05000_USA-road-d-NY.cha"

# TESTS avec listes chainées
temps_total=0.0
arg1=1
arg2=20
echo "------------ TESTS avec Liste chainée ${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"

# TESTS avec Arbre quaternaire
temps_total=0.0
arg1=3
echo "------------ TESTS avec Arbre quaternaire${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"


# TESTS 2
temps_total=0.0
arg1=2
arg2=10
echo "------------ TESTS avec Table Hashage${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
        arg2=$((${arg2}+5))
done

#test pour PLA
commande="./timer 07397_pla.cha"

# TESTS avec listes chainées
temps_total=0.0
arg1=1
arg2=20
echo "------------ TESTS avec Liste chainée ${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"

# TESTS avec Arbre quaternaire
temps_total=0.0
arg1=3
echo "------------ TESTS avec Arbre quaternaire${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
done

echo "Temps total : ${temps_total}"
#temps_moyen=$(echo "${temps_total} ${nombre_iterations}" | awk  '{print $1/$2}')
#echo "Temps moyen : ${temps_moyen}"


# Tests avec la table de Hashage
temps_total=0.0
arg1=2
arg2=10
echo "------------ TESTS avec Table Hashage${arguments} ------------"
for (( i=1; i<=${nombre_iterations}; i++ ))
do
        temps_i="$(time (${commande} ${arg1} ${arg2}) 2>&1 1>/dev/null)"
        echo "[${i}] ${temps_i}"
        temps_total=$(echo "${temps_total} ${temps_i}" | awk  '{print $1+$2}')
        arg2=$((${arg2}+5))
done