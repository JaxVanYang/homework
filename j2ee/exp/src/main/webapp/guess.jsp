<%--
  Created by IntelliJ IDEA.
  User: Rekord
  Date: 2022/1/1
  Time: 23:03
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Guess</title>
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
    <h1>登录</h1>
    <p>系统随机生成一个 1 到 100 之间的数</p>
    <p>请在下面的文本框中输入你猜的数</p>
    <form action="/guess-number-servlet" method="post">
        <input type="number" name="guessNumber"/>
        <input type="submit" value="提交"/>
    </form>
</div>
</body>
</html>
