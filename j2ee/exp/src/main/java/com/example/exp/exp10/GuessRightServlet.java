package com.example.exp.exp10;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "guessRightServlet", value = "/guess-right-servlet")
public class GuessRightServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        doPost(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html;charset=utf-8");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession();

        out.print("恭喜您!答对了!您一共猜了" + (int) session.getAttribute("totalCount") + "次");
        //将totalCount还原
        session.setAttribute("totalCount", 0);
        out.print("<a href='/input-number-servlet'>再玩一次</a>");
        out.close();
    }
}