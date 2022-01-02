package com.example.exp.exp11;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebFilter(filterName = "CheckoutFilter", urlPatterns = "/checkout.jsp")
public class CheckoutFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpSession session = ((HttpServletRequest) request).getSession();
        Boolean isLogin = (Boolean) session.getAttribute("isLogin");
        if (isLogin == null || !isLogin) {
            ((HttpServletResponse) response).sendRedirect("/cart-login.jsp?type=checkout");
        }
        chain.doFilter(request, response);
    }

    @Override
    public void destroy() {
    }
}
