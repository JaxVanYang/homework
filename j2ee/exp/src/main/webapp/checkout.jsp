<%@ page import="com.example.exp.exp11.Book" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: Rekord
  Date: 2022/1/2
  Time: 14:56
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>结算</title>
</head>
<body>
<%
    List<Book> cart = (List<Book>)session.getAttribute("cart");
    if (cart != null) {
        cart.clear();
    }
%>

<p>谢谢惠顾，欢迎下次再来！</p>
<p><a href="/list-book-servlet">继续购物</a></p>
</body>
</html>
