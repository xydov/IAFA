#!/bin/bash

# Vérifier si l'adresse e-mail du destinataire a été fournie en tant qu'argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <destinataire>"
    exit 1
fi

# Adresse e-mail du destinataire
recipient="$1"

# Adresse e-mail de l'expéditeur (votre adresse Gmail)
sender="noahchelgham@gmail.com"

# Mot de passe de votre compte Gmail
password="NOAHchel23.01.2002"

# Sujet de l'e-mail
subject="Test d'envoi d'e-mail depuis un script shell"

# Corps du message
message="Ceci est un test d'envoi d'e-mail depuis un script shell."

# Créer le corps de l'e-mail au format JSON
email_data=$(cat <<EOF
{
  "personalizations": [
    {
      "to": [
        {
          "email": "$recipient"
        }
      ]
    }
  ],
  "from": {
    "email": "$sender"
  },
  "subject": "$subject",
  "content": [
    {
      "type": "text/plain",
      "value": "$message"
    }
  ]
}
EOF
)

# Envoyer l'e-mail en utilisant l'API Gmail et curl
curl -s --request POST \
  --url 'https://api.sendgrid.com/v3/mail/send' \
  --header "Authorization: Bearer $SENDGRID_API_KEY" \
  --header 'Content-Type: application/json' \
  --data "$email_data"

# Afficher un message de confirmation
echo "L'e-mail a été envoyé à $recipient."

