package com.example.exp.exp11;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet(name = "purchaseServlet", value = "/purchase-servlet")
public class PurchaseServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String id = req.getParameter("id");
        if (id == null) {
            String url = "/list-book-servlet";
            resp.sendRedirect(url);
            return;
        }

        Book book = BookDb.getBook(id);
        HttpSession session = req.getSession();
        List<Book> cart = (List<Book>) session.getAttribute("cart");
        if (cart == null) {
            cart = new ArrayList<Book>();
            session.setAttribute("cart", cart);
        }

        boolean flag = true;
        for (Book b : cart) {
            if (b.getId().equals(book.getId())) {
                b.addCount();
                flag = false;
                break;
            }
        }
        if (flag) {
            cart.add(book);
        }

        Cookie cookie = new Cookie("JSESSIONID", session.getId());
        cookie.setMaxAge(3600);
        resp.addCookie(cookie);
        String url = "/cart.jsp";
        resp.sendRedirect(url);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
