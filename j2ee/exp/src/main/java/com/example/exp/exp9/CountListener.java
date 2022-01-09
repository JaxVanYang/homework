package com.example.exp.exp9;

import com.example.exp.model.Counter;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.ServletRequestEvent;
import javax.servlet.ServletRequestListener;
import javax.servlet.annotation.WebListener;
import java.io.*;
import java.util.Properties;

@WebListener
public class CountListener implements ServletRequestListener, ServletContextListener {
    private static final String url = "/listener-count.properties";
    private static Counter counter = null;

    public static Counter getCounter() {
        return counter;
    }

    @Override
    public void requestInitialized(ServletRequestEvent sre) {
        if (counter == null) {
            counter = new Counter();

            InputStream in = sre.getServletContext().getResourceAsStream(url);

            Properties pros = new Properties();
            try {
                pros.load(in);
            } catch (IOException e) {
                e.printStackTrace();
            }
            counter.setCount(Integer.parseInt(pros.getProperty("count")));
        }
        counter.add();
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        if (counter == null) return;

        Properties pros = new Properties();
        pros.setProperty("count", Integer.toString(counter.getCount()));
        try {
            FileOutputStream out = new FileOutputStream(sce.getServletContext().getRealPath(url));
            pros.store(out, "CountListener");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
