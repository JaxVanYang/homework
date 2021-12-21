package SimpleFactory;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an operation:");
        String operation = scanner.next();
        Operation op = OperationFactory.CreateOperation(operation);

        System.out.println("Enter a number:");
        double a = scanner.nextDouble();
        System.out.println("Enter another number:");
        double b = scanner.nextDouble();

        if (op != null) {
            System.out.println("The result is : " + op.calc(a, b));
        } else {
            System.out.println("Error!");
        }
    }
}
