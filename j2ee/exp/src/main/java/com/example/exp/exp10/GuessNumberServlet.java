package com.example.exp.exp10;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "guessNumberServlet", value = "/guess-number-servlet")
public class GuessNumberServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print("Hello");
        out.close();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        HttpSession session = request.getSession();
        //猜数次数加一
        session.setAttribute("totalCount", (int) session.getAttribute("totalCount") + 1);

        String guessNumber = request.getParameter("guessNumber");
        response.setContentType("text/html;charset=utf-8");
        PrintWriter out = response.getWriter();
        String status = "";
        String url = "/input-number-servlet";
        do {
            if (guessNumber.strip() == "") {
                //空串
                break;
            }
            try {
                int number = Integer.valueOf(guessNumber);
                if (number < 1 || number > 100) {
                    // System.out.println("数字过大或过小");
                    break;
                }

                int guess = (int) session.getAttribute("GUESS");
                if (guess > number) {
                    status = "您猜的价格小了";
                } else if (guess < number) {
                    status = "您猜的价格大了";
                } else {
                    url = "/guess-right-servlet";
                }
            } catch (NumberFormatException e) {
                //非数字
                break;
            }
        } while (false);
        session.setAttribute("status", status);
        response.sendRedirect(url);
        out.close();
    }
}