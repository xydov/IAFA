package jeuDeLoie;

public class Journal {

    private String message = "";

    public void ajouterMessage(String message) {
        this.message = this.message + message;
        //  this.message.concat(message);
    }

    public void afficherMessage()
    {
        System.out.println(message);
        message = "";
    }
}
