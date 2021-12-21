package Adapter;

interface Target {
    void showMsg();
}

class Adaptee {
    public void specialMsg() {
        System.out.println("This is a special message.");
    }
}

public class Adapter implements Target {
    private Adaptee adaptee;

    public Adapter(Adaptee adaptee) {
        this.adaptee = adaptee;
    }

    @Override
    public void showMsg() {
        adaptee.specialMsg();
    }
}
