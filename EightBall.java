import java.util.Random;
import java.util.Scanner;

public class EightBall {
    public static void  main(String[] args){
        System.out.println("enter question");

        Scanner scan = new Scanner(System.in);
        scan.next();
        scan.close();

        Random rand = new Random();

        int r = rand.nextInt(10) ;

        if (r == 0){
            System.out.println("As I see it, yes.");
        } else if (r == 1) {
            System.out.println("As I see it, yes.");
        } else if (r == 2) {
            System.out.println("NO, you baboon fecal matter");
        } else if (r == 3) {
            System.out.println("Sorry, I lost my kidney in Rio de Janero, can't talk right now");
        } else if (r == 4) {
            System.out.println("Datebayo");
        }else if (r == 5){
            System.out.println("Nesijaudink, savaiteje yra 3000 valandu");
        } else if (r == 6) {
            System.out.println("As esu saules tevas, sunus arba Madrido era");
        } else if (r == 7) {
            System.out.println("Striukes nelauzyk isplautos rankos");
        } else if (r == 8) {
            System.out.println("Stalas nevaldiskas");
        } else if (r == 9) {
            System.out.println("Spagetis be s");
        }





    }
}
