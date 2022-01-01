package com.example.exp;

import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Enumeration;
import java.util.Properties;

@WebServlet(name = "helloServlet", value = "/hello-servlet")
public class HelloServlet extends HttpServlet {
    private String message;

    public void init() {
        message = "Hello World!";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");

        // Hello
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>" + message + "</h1>");

        ServletContext context = getServletContext();
        Enumeration<String> names = context.getInitParameterNames();
        while (names.hasMoreElements()) {
            String name = names.nextElement();
            String val = context.getInitParameter(name);
            out.println("<p>" + name + " = " + val + "</p>");
        }

        InputStream in = context.getResourceAsStream("/WEB-INF/classes/data.properties");
        Properties pros = new Properties();
        pros.load(in);
        out.println("<p>Project Name: " + pros.getProperty("ProjectName") + "</p>");

        out.println("</body></html>");
    }

    public void destroy() {
    }
}