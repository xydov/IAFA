import humain.*;

public class MonHistoire {
    public static void main(String [] args) {

        Humain h = new Humain("Prof", 10, "Porto");

        h.direBonjour ();
        h.boire ();

        Commercant c = new Commercant("Marchand", 35);

        c.direBonjour ();

        Yakusa y = new Yakusa("Yaku␣le␣noir", 42,

                "biere", "WarSong");

        y.extorquer(c);

        Ronin r = new Ronin("Roro", 61, "sake");

        r.donner (10, c );
        r.provoquer(y);
        r.direBonjour ();

        Samourai s = new Samourai("Samouraiiii" , 20 , "the", "Miyamoto");
        s.boire();
        s.boire("cidre");
        s.direBonjour();

        Traitre t = new Traitre("Philouu", 1, "traitrise", "Maximus-Bullitus");
        t.direBonjour();

        GrandMere gh = new GrandMere("Gisele", 250);
        gh.faireConnaissanceAvec(s);
        gh.faireConnaissanceAvec(r);
        gh.faireConnaissanceAvec(t);
        gh.direBonjour();
        gh.ragoter();

        Potier p = new Potier("Pedro potierie", 367, "biere");
        p.creerUnePoterie("Valhala");
        p.annoncerStock();
        p.vendre(4, t, 16);
    }
}