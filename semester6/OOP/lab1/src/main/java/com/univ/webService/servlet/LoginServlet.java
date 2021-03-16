package com.univ.webService.servlet;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.univ.webService.DAO.UserDAO;
import com.univ.webService.dataModel.User;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        System.out.println("wow");
        HttpSession session = request.getSession();
        if (session.getAttribute("sessionId") == null) {
            session.setAttribute("sessionId", Constants.LOGIN_ACCOUNT);
        }
        if (request.getParameter("sessionId") != null) {
            session.setAttribute("sessionId", request.getParameter("sessionId"));
        }

        JsonObject data = new Gson().fromJson(request.getReader(), JsonObject.class);

        String password = data.get("password").getAsString();
        String login = data.get("login").getAsString();

        try {
            // UserDAO abonentDAO = (UserDAO) BeanFactory.getBean(UserDAO.class);
            List<User> abonent = new ArrayList<>();
            abonent = UserDAO.getUserFromDB(Constants.SELECT_ALL_INT, login, password, Constants.SELECT_ALL_INT);
            String json = new Gson().toJson(abonent.get(0));
            response.addHeader("Access-Control-Allow-Origin", "http://localhost:5000");
            response.setContentType("application/json");
            response.setCharacterEncoding("UTF-8");
            response.getWriter().write(json);
            System.out.println(json);
            // ((LoginService)
            // BeanFactory.getBean(LoginService.class)).loginAccount(session, request,
            // password, login, abonentDAO);
        } catch (SQLException e) {
            request.getRequestDispatcher("Error.jsp").forward(request, response);
        }
        // request.getRequestDispatcher("response.jsp").forward(request, response);

    }

}
