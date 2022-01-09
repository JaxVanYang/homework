package com.example.exp;

import com.example.exp.model.Counter;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.util.Properties;

@WebServlet(name = "counterServlet", value = "/counter-servlet", loadOnStartup = 1)
public class CounterServlet extends HttpServlet {
    private static Counter counter = null;
    private static final String url = "/count.properties";

    @Override
    public void init() throws ServletException {
        if (counter == null) {
            InputStream in = getServletContext().getResourceAsStream(url);

            Properties pros = new Properties();
            try {
                pros.load(in);
            } catch (IOException e) {
                e.printStackTrace();
            }
            counter = new Counter();
            counter.setCount(Integer.parseInt(pros.getProperty("count")));
        }
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        counter.add();
        resp.setContentType("text/html;charset=utf-8");
        PrintWriter out = resp.getWriter();
        out.println("<h1>计数器的值为：" + counter.getCount() + "</h1>");
    }

    @Override
    public void destroy() {
        Properties pros = new Properties();
        pros.setProperty("count", Integer.toString(counter.getCount()));
        try {
            FileOutputStream out = new FileOutputStream(getServletContext().getRealPath(url));
            pros.store(out, "CounterServlet");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
