package com.example.exp.exp11;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;

public class BookDb {
    private static Map<String, Book> books = new LinkedHashMap<>();

    static {
        books.put("1", new Book("1", "Java", 23.5));
        books.put("2", new Book("2", "C++", 25.5));
        books.put("3", new Book("3", "C#", 27.5));
        books.put("4", new Book("4", "Python", 29.5));
        books.put("5", new Book("5", "PHP", 19.5));
        books.put("6", new Book("6", "Ruby", 21.5));
    }

    public static Book getBook(String id) {
        return new Book(books.get(id));
    }

    public static Collection<Book> getAll() {
        return books.values();
    }
}
