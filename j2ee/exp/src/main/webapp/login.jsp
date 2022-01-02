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
    <h1>登录</h1>
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
