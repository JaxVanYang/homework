<%@ page import="com.example.exp.exp11.Book" %>
<%@ page import="java.util.List" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>购物车</title>

    <style>
        .container {
            width: 400px;
            margin: 0 auto;
        }

        h1 {
            text-align: center;
        }

        .center {
            text-align: center;
        }
    </style>
</head>
<body>
<div class="container">
    <h1>购物车</h1>
    <%
        List<Book> cart = null;
        if (session != null) {
            cart = (List<Book>) session.getAttribute("cart");
        }

        if (cart == null || cart.isEmpty()) {
            out.write("<p>购物车为空</p>");
            out.write("<p><a href='/list-book-servlet'>返回首页</a></p>");
            return;
        }
    %>
    <p>您购买的商品如下：</p>
    <table class="center">
        <tr>
            <th>书名</th>
            <th>价格</th>
            <th>数量</th>
            <th>小计</th>
            <th>加一</th>
            <th>减一</th>
        </tr>
        <%
            double total = 0;
            for (Book book : cart) {
                total += book.getTotalPrice();
                out.write("<tr>");
                out.write("<td>" + book.getName() + "</td>");
                out.write("<td>￥" + book.getPrice() + "</td>");
                out.write("<td>" + book.getCount() + "</td>");
                out.write("<td>￥" + book.getTotalPrice() + "</td>");
                out.write("<td><a href='/cart-servlet?type=add&id=" + book.getId() + "'>+</a></td>");
                out.write("<td><a href='/cart-servlet?type=reduce&id=" + book.getId() + "'>-</a></td>");
                out.write("</tr>");
            }
        %>
        <tr>
            <td colspan="3">总计</td>
            <td>￥<%= total %>
            </td>
        </tr>
    </table>
    <p>
        <a href="/list-book-servlet">继续购物</a>
        <a href="checkout.jsp">结算</a>
        <a href="/cart-servlet?type=clear">清空购物车</a>
        <a href="/cart-servlet?type=logout">退出登录</a>
    </p>
</div>
</body>
</html>
