<%--
  Created by IntelliJ IDEA.
  User: jax
  Date: 2022/1/1
  Time: 下午6:31
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
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
    <h1>Login</h1>
    <form action="/reg-servlet" method="post">
        <p><label>
            用户名：
            <input type="text" name="username"/>
        </label></p>
        <p><label>
            密码&nbsp;&nbsp;&nbsp;&nbsp;：
            <input type="password" name="password"/>
        </label></p>
        <p class="center"><input type="submit" value="登录"/></p>
    </form>
</div>
</body>
</html>
