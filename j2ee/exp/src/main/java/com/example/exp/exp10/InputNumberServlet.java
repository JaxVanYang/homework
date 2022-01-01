package com.example.exp.exp10;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

@WebServlet(name = "inputNumberServlet", value = "/input-number-servlet")
public class InputNumberServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        response.setContentType("text/html;charset=utf-8");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession();

        Object totalCountObj = session.getAttribute("totalCount");
        String status = (String) session.getAttribute("status");
        if (status != null && status.strip() != "") {
            out.println(status + "<br>");
        }
        if (totalCountObj == null || totalCountObj.toString().equals("0")) {
            //第一次访问
            session.setAttribute("totalCount", 0);
            int GUESS = Math.abs(new Random().nextInt()) % 100 + 1;
            session.setAttribute("GUESS", GUESS);
            System.out.println("第一次访问，设定GUESS=" + GUESS);
        }
        Cookie cookie = new Cookie("GSESSIONID", session.getId());
        cookie.setPath("/ex8");
        response.addCookie(cookie);


        request.getRequestDispatcher("/guess.jsp").include(request, response);
        out.close();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        doGet(request, response);
    }

}
