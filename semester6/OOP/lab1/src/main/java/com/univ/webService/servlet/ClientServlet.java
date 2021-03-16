package com.univ.webService.servlet;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.univ.webService.DAO.BookDAO;
import com.univ.webService.dataModel.Book;

@WebServlet("/client")
public class ClientServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        JsonObject act = new Gson().fromJson(req.getReader(), JsonObject.class);
        switch (act.get("action").getAsString()) {

        case "listbooks":
            resp.addHeader("Access-Control-Allow-Origin", "http://localhost:5000");
            resp.setContentType("application/json");
            resp.setCharacterEncoding("UTF-8");
            ArrayList<Book> books = BookDAO.getBooksFromDB(Constants.SELECT_ALL_INT, Constants.SELECT_ALL_STR);
            String json = new Gson().toJson(books);
            resp.getWriter().write(json);
            break;
        }
    }
}
