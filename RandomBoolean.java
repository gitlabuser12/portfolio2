import java.util.Random;

public class RandomBoolean {

    public static void main(String[] args) {
        Random rng = new Random();
        int attemptNr = 0;

        while (true) {
            int finish = 0;
            attemptNr += 1;

            for (int i = 1; i < 6; i++) {
                int a = rng.nextInt(2);
                boolean door = (a == 0);
                System.out.println(door);

                if (door) {
                    System.out.println("You've passed the " + i + " door");
                } else {
                    System.out.println("You failed :[");
                    break;
                }
                finish = i;
                if (i == 5) {
                    System.out.println("Congratulations you've won!!!");
                    break;
                }

            }
            System.out.println(finish);
            if (finish == 5) {
                System.out.println("Number of attempts: " + attemptNr);
                break;
            }
        }
    }
}