package com.example.exp.exp11;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

@WebServlet(name = "cartServlet", value = "/cart-servlet")
public class CartServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        PrintWriter out = resp.getWriter();
        List<Book> cart = null;
        HttpSession session = req.getSession(false);
        if (session != null) {
            cart = (List<Book>) session.getAttribute("cart");
        }
        if (cart == null) {
            cart = new ArrayList<Book>();
        }

        String type = req.getParameter("type");
        String id = req.getParameter("id");

        if ("add".equals(type)) {
            resp.sendRedirect("/purchase-servlet?id=" + id);
        } else if ("reduce".equals(type)) {
            for (Book book : cart) {
                if (book.getId().equals(id)) {
                    book.setCount(book.getCount() - 1);

                    if (book.getCount() == 0) {
                        cart.remove(book);
                    }
                    break;
                }
            }
            resp.sendRedirect("/cart.jsp");
        } else if ("clear".equals(type)) {
            cart.clear();
            resp.sendRedirect("/cart.jsp");
        } else if ("logout".equals(type)) {
            boolean flag = true;

            if (session != null) {
                Boolean isLogin = (Boolean) session.getAttribute("isLogin");
                if (isLogin != null && isLogin) {
                    out.write("<p>退出登录成功</p>");
                    out.write("<p><a href='/list-book-servlet'>继续购物</a></p>");
                    flag = false;
                }
                session.invalidate();
            }

            if (flag) {
                out.write("<p>您还没有登录</p>");
                out.write("<p><a href='/cart-login.jsp'>登录</a></p>");
                out.write("<p><a href='/list-book-servlet'>继续购物</a></p>");
            }
        }
    }
}
