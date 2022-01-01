package com.example.exp.exp9;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebInitParam;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(
        name = "regServlet",
        value = "/reg-servlet",
        initParams = {
                @WebInitParam(name = "好运来", value = "123456"),
        }
)
public class RegServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setCharacterEncoding("UTF-8");
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        ServletConfig config = getServletConfig();

//        Enumeration<String> initParameterNames = config.getInitParameterNames();
//        while (initParameterNames.hasMoreElements()) {
//            String name = initParameterNames.nextElement();
//            System.out.println(name + ":" + config.getInitParameter(name));
//        }

        if (password.equals(config.getInitParameter(username))) {
            req.setAttribute("username", username);
            RequestDispatcher dispatcher = req.getRequestDispatcher("/login-success-servlet");
            dispatcher.forward(req, resp);
        } else {
            RequestDispatcher dispatcher = req.getRequestDispatcher("/login-fail-servlet");
            dispatcher.forward(req, resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
