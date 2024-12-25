#! /bin/bash
set -o pipefail

DIR=$(pwd)
my_id=""
declare -A NoncePour


function hex_to_binary () {
    xxd -r -p
}
function binary_to_hex () {
    xxd  -p
}

function to_base64 () {
    openssl base64
}
function from_base64 () {
    openssl base64 -d
}

function remove_newlines() {
    tr -d '\n'
}
function add_newline_format() {
    fold -w 64 
}

function group () {
    to_base64 | sed -e 's/\(.*\)/{\1}/'
}
function ungroup () {
    sed -e 's/{\([^}]*\)}/\1/' | from_base64
}

function hash () {
    sha256sum | awk '{print $1}' 
}

function clefs_rsa () {
    if [ -z "${1}" ] ; then
	pub="clef_publique"
	priv="clef_privee"
    else
	pub="${1}_pub"
	priv="${1}"
    fi
    openssl genrsa -F4 -out "${priv}.pem"
    openssl rsa -in "${priv}.pem" -out "${pub}.pem" -pubout
    echo "la clef publique est dans ${pub}.pem"
    echo "la clef privée est dans ${priv}.pem"
}

function ajoute_clef_publique () {
    local message
    message=(${1//:/ })
    echo "-----BEGIN PUBLIC KEY-----" >  "${message[0]}.pem"
    echo "${message[1]}"  | fold -w 64 >> "${message[0]}.pem"
    echo "-----END PUBLIC KEY-----" >>  "${message[0]}.pem"
}


function rsa_chiffre_pour () {
    openssl rsautl -encrypt -oaep -inkey  "${1}.pem" -pubin |  to_base64 | remove_newlines
}
function rsa_dechiffre () {
    from_base64 | openssl rsautl -decrypt -oaep -inkey clef_privee.pem
}

function rsa_signe () {
    openssl rsautl -sign -inkey clef_privee.pem | to_base64
}
function rsa_signature_de () {
    from_base64 | openssl rsautl -verify -inkey "${1}.pem"  -pubin
}


function concatenate () {
    local res
    local -a other_args
    read -a otherargs
    res="${otherargs[0]}"
    for part in ${otherargs[@]:1} ; do
	res="${res}:${part}"
    done
    echo ${res} 
}
function projection () {
    # ungroup | IFS=":" read -a ${1}
    sed -e 's/:/ /g'
}


function rsa_digest_creation () {
    hash | rsa_signe  | remove_newlines
}
function rsa_digest_valide_origine () {
    rsa_signature_de "${1}" 
}

function rsa_signature () {
    local message
    read message
    echo "$(echo ${message} | group  | remove_newlines)@$(echo  "${message}" | rsa_digest_creation  )" 
}
function rsa_signature_verification () {
    local origine Mesg resultat  somme_hash somme_hash_signee
    origine=$1
    IFS='@' read -ra Mesg 
    somme_hash=$(echo ${Mesg[0]} | ungroup | hash )
    somme_hash_signee=$(echo "${Mesg[1]}" | rsa_digest_valide_origine "${origine}")
    if [  "${somme_hash}" = "${somme_hash_signee}" ] ; then
	echo "${origine} a signé le message: $(echo ${Mesg[0]} | ungroup)"
    else
	echo "${origine} n'a pas signé ce message"
    fi
}

function publie_clef_publique() {
    local id
    id=$1
    my_id=${id}
    echo "ajoute_clef_publique ${id}:$(sed '1d; $d' clef_publique.pem | remove_newlines)" 
}

function fresh() {
    xxd -l 16 -p /dev/urandom
}

function AlicenBobPrintf() {
    printf "${1} -> ${2} : ${3}\n"
}

function ping_securise_message1() {
    local message
    NoncePour[${2}]=$(fresh)
    echo "envoi du nonce ${NoncePour[${2}]} à ${2}"
    #    message=$(echo "${id}" "${nonce}" | concatenate | rsa_chiffre_pour "${destinataire}" )
    if [ ! -e "${2}.pem" ] ; then
	echo "vous devez d'abord récupérer sa clef publique."
	return 1
    fi
    message=$(echo "${1}" "${NoncePour[${2}]}" | concatenate | rsa_chiffre_pour "${2}" )
    echo ${message}
    AlicenBobPrintf "${1}" "${2}" $(echo "${1}" "${NoncePour[${2}]}" | concatenate | rsa_chiffre_pour "${2}" )
    1>&2 printf "nonce utilisé: ${NoncePour[${2}]}\n"
    return 0
}

function ping_securise_message2 () {
    local -a  donnees
    donnees=($(echo ${3} | rsa_dechiffre | projection ) )
    if [ "${donnees[0]}" != "${2}" ] ; then
	echo "émetteur annoncé: ${2}"
	echo "émetteur réel: ${donnees[0]}"
	return 1
    fi
    NoncePour[${2}]=$(fresh)
    #    message=$(echo "${donnees[1]}" "${nonce}" | concatenate | rsa_chiffre_pour "${2}" )
    printf "émetteur: %s\nnonce : %s\nréponse (avec nonce ${NoncePour[${2}]}):\n" "${donnees[0]}" "${donnees[1]}"
    AlicenBobPrintf  "${1}"  "${2}"  $(echo "${donnees[1]}" "${NoncePour[${2}]}"  | concatenate  | rsa_chiffre_pour "${2}" )
    echo "nonce renvoyé (à vérifier avant de conclure): ${nonce}"
    return 0
}

function ping_securise_message3 () {
    local -a donnees 
    donnees=($(echo $3 | rsa_dechiffre | projection ))
    #    IFS=":" read -ra  donnees <<< "${clair}"
    #    IFS=" "
#    echo "nonce renvoyé (à vérifier avant de répondre): ${donnees[0]}"
#    if [ "${donnees[0]}" != "${NoncePour[${2}]}" ] ; then
#	echo "le nonce n'est pas bon"
#	return 1
#    fi
    #    message=$(echo "${donnees[1]}" | rsa_chiffre_pour "${2}" )
    AlicenBobPrintf "${1}"  "${2}"  $(echo "${donnees[1]}" | rsa_chiffre_pour "${2}" )
    return 0
}


function ping_securise_conclusion () {
    local donnees clair  messsage
    clair=$(echo $3 | rsa_dechiffre )
    echo "nonce renvoyé par $2 (à vérifier avant de conclure): ${clair}"
#    if [ "${clair}" != "${NoncePour[${2}]}" ] ; then
#	echo "le nonce n'est pas bon"
#	return 1
#    fi
    return 0
}

function ping_securise_initiateur () {
    local id correspondant msg reponse
    if [ -z "${my_id}" ] ; then
	echo "Quelle est votre identité ?"
	read -e my_id
    fi
    echo "Avec qui voulez-vous communiquer ?"
    read -e correspondant
    if [ ! -e "${correspondant}.pem" ] ; then
	echo "Il faut d'abord récupérer sa clef publique."
    else
	if ! ping_securise_message1 "${my_id}" "${correspondant}" ; then
	    return 1
	fi
	echo "Quelle est la réponse ?"
	read -a Msg
	until ping_securise_message3 "${my_id}" "${correspondant}" "${Msg[4]}" ; do
	    echo -n "Erreur dans le message reçu. Entrez 'n' pour arrêter la session ?"
	    read reponse
	    if [ "${reponse}" = "n" ] ; then
		return 1
	    fi
	    echo "Quelle est la réponse ?"
	    read -a Msg
	done
    fi
    echo "Exécution avec ${correspondant} terminée avec succès."
    return 0
}
function ping_securise_repondeur () {
    local id correspondant reponse
    declare -a Msg
    
    echo "Quel message vous a été adressé ?"
    read -a Msg
    # Msg[0] : initiator, Msg[2]: moi , Msg[4] : message

    if [ -z "${my_id}" ] ; then
	my_id=${Msg[2]}
    fi
    if [ ! -e "${Msg[0]}.pem" ] ; then
	echo "Il faut d'abord récupérer la clef publique de ${Msg[0]}."
	return 1
    fi
    correspondant=${Msg[0]}
    if [ "${Msg[2]}" != "${my_id}" ] ; then
	echo "Ce message ne vous est pas adressé (ou changez votre identité)"
	return 1
    fi
    echo "message recu: ||${Msg[4]}|| de ||${Msg[0]}||"
    ping_securise_message2 "${Msg[2]}" "${Msg[0]}" "${Msg[4]}"
    echo "Quelle est la réponse ?"
    read -a Msg
    until ping_securise_conclusion "${Msg[2]}" "${Msg[0]}" "${Msg[4]}" ; do
	echo -n "Erreur dans le message reçu. Entrez 'n' pour arrêter la session: "
	read reponse
	if [ "${reponse}" = "n" ] ; then
	    return 1
	fi
	echo "Quelle est la réponse ?"
	read -a Msg
    done
    echo "Exécution avec ${correspondant} terminée avec succès."
}

