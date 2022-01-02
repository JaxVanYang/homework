package com.example.exp.exp11;

import java.io.Serializable;

public class Book implements Serializable {
    private String id;
    private String name;
    private double price = 1.0;
    private int count = 1;

    public Book(Book book) {
        this.id = book.id;
        this.name = book.name;
        this.price = book.price;
        this.count = book.count;
    }

    public Book(String id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public Book(String id, String name, double price, int count) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.count = count;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public double getTotalPrice() {
        return price * count;
    }

    public void addCount() {
        count++;
    }

    @Override
    public String toString() {
        return "Book{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", price=" + price +
                ", count=" + count +
                '}';
    }
}
