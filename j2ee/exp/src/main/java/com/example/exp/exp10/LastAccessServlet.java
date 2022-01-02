package com.example.exp.exp10;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

@WebServlet(name = "lastAccessServlet", value = "/last-access-servlet")
public class LastAccessServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html;charset=UTF-8");


        PrintWriter out = resp.getWriter();
        String lastAccessTime = null;
        Cookie[] cookies = req.getCookies();

        for (Cookie cookie : cookies) {
            if ("lastAccess".equals(cookie.getName())) {
                lastAccessTime = cookie.getValue();
                break;
            }
        }

        if (lastAccessTime == null) {
            out.println("您是首次访问本站！");
        } else {
            out.println("您上次访问的时间是：" + lastAccessTime);
        }

        String currentTime = new SimpleDateFormat("yyyy-MM-dd:hh:mm:ss").format(new Date());
        Cookie cookie = new Cookie("lastAccess", currentTime);
        System.out.println("cookie: " + cookie);
        resp.addCookie(cookie);

        for (Cookie it : req.getCookies()) {
            System.out.println("name = " + it.getName() + " value = " + it.getValue());
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
