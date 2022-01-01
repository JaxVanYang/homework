package com.example.exp.model;

public class Counter {
    private int count; //计数值

    public Counter() {
        this(0);
    }

    public Counter(int count) {
        this.count = count;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public void add() {
        count++;
    }
}