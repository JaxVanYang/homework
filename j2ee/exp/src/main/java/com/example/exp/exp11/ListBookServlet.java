package com.example.exp.exp11;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collection;

@WebServlet(name = "listBookServlet", value = "/list-book-servlet")
public class ListBookServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        PrintWriter out = resp.getWriter();

        Collection<Book> books = BookDb.getAll();
        out.write("<p>本站提供的图书有：</p>");
        for (Book book : books) {
            String url = "/purchase-servlet?id=" + book.getId();
            out.write("<p>《" + book.getName() + "》￥" + book.getPrice() + "<a href=\"" + url + "\">点击购买</a></p>");
        }
        out.write("<p><a href=\"/cart-login.jsp\">登录</a></p>");
        out.write("<p><a href=\"/cart.jsp\">查看购物车</a></p>");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
