package com.example.exp.exp9;

import javax.imageio.ImageIO;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;

@WebServlet(name = "imageServlet", value = "/image-servlet")
public class ImageServlet extends HttpServlet {
    private final Font font = new Font("Courier", Font.BOLD, 12);  //字体

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //得到待显示的数字
        String count = String.valueOf(CountListener.getCounter().getCount());
        int len = count.length(); //数字的长度
        response.setContentType("image/jpeg");
        ServletOutputStream out = response.getOutputStream();
        //创建一个位于缓存中的图像，长为11*len，高为16
        BufferedImage image = new BufferedImage(11 * len, 16, BufferedImage.TYPE_INT_RGB);
        //获得Graphics画笔
        Graphics g = image.getGraphics();
        g.setColor(Color.black);
        //画一个黑色的矩形，长为11*len，高为16
        g.fillRect(0, 0, 11 * len, 16);
        g.setColor(Color.white);
        g.setFont(font);
        char c;
        for (int i = 0; i < len; i++) {
            c = count.charAt(i);
            g.drawString(c + "", i * 11 + 1, 12); //写一个白色的数字
//            g.drawLine((i + 1) * 11 - 1, 0, (i + 1) * 11 - 1, 16); //画一个白色的竖线
        }
        ImageIO.write(image, "jpg", out);
        out.close();
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}