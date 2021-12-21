package SimpleFactory;

interface Operation {
    double calc(double a, double b);
}

class Add implements Operation {
    @Override
    public double calc(double a, double b) {
        return a + b;
    }
}

class Sub implements Operation {
    @Override
    public double calc(double a, double b) {
        return a - b;
    }
}

class Mul implements Operation {
    @Override
    public double calc(double a, double b) {
        return a * b;
    }
}

class Div implements Operation {
    @Override
    public double calc(double a, double b) {
        return a / b;
    }
}

public class OperationFactory {
    public static Operation CreateOperation(String operation) {
        if ("+".equals(operation)) {
            return new Add();
        } else if ("-".equals(operation)) {
            return new Sub();
        } else if ("*".equals(operation)) {
            return new Mul();
        } else if ("/".equals(operation)) {
            return new Div();
        }
        return null;
    }
}