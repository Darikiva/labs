package com.univ.webService.servlet;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.univ.webService.DAO.RequestBookDAO;
import com.univ.webService.dataModel.RequestBook;

@WebServlet("/librarian")
public class LibrarianServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        JsonObject act = new Gson().fromJson(req.getReader(), JsonObject.class);
        System.out.println("wow");
        resp.addHeader("Access-Control-Allow-Origin", "http://localhost:5000");
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");
        switch (act.get("action").getAsString()) {
        case Action.ACCEPT_BOOK:
            RequestBookDAO.acceptRequest(act.get("id_user").getAsInt(), act.get("id_book").getAsInt());
            break;
        case Action.LIST_REQUESTS: {
            ArrayList<RequestBook> reqs = RequestBookDAO.getBookRequests(Constants.SELECT_ALL_INT,
                    Constants.SELECT_ALL_INT);
            String json_reqs = new Gson().toJson(reqs);
            resp.getWriter().write(json_reqs);
        }
            break;
        case Action.REFUSE_BOOK: {
            int id_user = act.get("id_user").getAsInt();
            int id_book = act.get("id_book").getAsInt();
            ArrayList<RequestBook> reqs = RequestBookDAO.getBookRequests(id_user, id_book);
            Answer answer;
            if (reqs.isEmpty()) {
                answer = new Answer(false, "No such request");
            } else if (reqs.get(0).isAccepted()) {
                answer = new Answer(false, "Already accepted");
            } else {
                RequestBookDAO.deleteRequest(id_user, id_book);
                answer = new Answer(true, "Success");
            }
            String json_ans = new Gson().toJson(answer);
            resp.getWriter().write(json_ans);
        }
            break;
        }
    }
}
