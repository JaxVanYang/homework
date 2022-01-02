package com.example.exp.exp11;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebInitParam;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet(
        name = "cartLoginServlet",
        value = "/cart-login-servlet",
        initParams = {
                @WebInitParam(name = "好运来", value = "123456"),
        }
)
public class CartLoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String type = req.getParameter("type");

        String username = req.getParameter("username");
        String password = req.getParameter("password");
        ServletConfig config = getServletConfig();

        if (password.equals(config.getInitParameter(username))) {
            HttpSession session = req.getSession();
            session.setAttribute("isLogin", Boolean.TRUE);
            Cookie cookie = new Cookie("JSESSIONID", session.getId());
            cookie.setMaxAge(3600);
            resp.addCookie(cookie);

            if ("checkout".equals(type)) {
                RequestDispatcher rd = req.getRequestDispatcher("/checkout.jsp");
                rd.forward(req, resp);
            } else {
                RequestDispatcher dispatcher = req.getRequestDispatcher("/list-book-servlet");
                dispatcher.forward(req, resp);
            }
        } else {
            RequestDispatcher dispatcher = req.getRequestDispatcher("/cart-login.jsp");
            dispatcher.forward(req, resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}