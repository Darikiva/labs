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
import com.univ.webService.DAO.BookDAO;
import com.univ.webService.DAO.ReadingDAO;
import com.univ.webService.DAO.RequestBookDAO;
import com.univ.webService.dataModel.Book;
import com.univ.webService.dataModel.Reading;
import com.univ.webService.dataModel.RequestBook;

@WebServlet("/client")
public class ClientServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        JsonObject act = new Gson().fromJson(req.getReader(), JsonObject.class);
        System.out.println("wow");
        resp.addHeader("Access-Control-Allow-Origin", "http://localhost:5000");
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");
        switch (act.get("action").getAsString()) {
        case Action.REQUEST_BOOK:
            RequestBookDAO.addRequest(act.get("id_user").getAsInt(), act.get("id_book").getAsInt());
            break;
        case Action.LIST_BOOKS: {
            ArrayList<Book> books = BookDAO.getBooksFromDB(Constants.SELECT_ALL_INT, Constants.SELECT_ALL_STR);
            String json_books = new Gson().toJson(books);
            System.out.println(json_books);
            resp.getWriter().write(json_books);
        }
            break;
        case Action.LIST_REQUESTS: {
            ArrayList<RequestBook> reqs = RequestBookDAO.getBookRequests(act.get("id_user").getAsInt(),
                    Constants.SELECT_ALL_INT);
            String json_reqs = new Gson().toJson(reqs);
            resp.getWriter().write(json_reqs);
        }
            break;
        case Action.TAKE_BOOK: {
            int id_user = act.get("id_user").getAsInt();
            int id_book = act.get("id_book").getAsInt();
            Answer answer;
            if (ReadingDAO.getReadings(id_user, Constants.SELECT_ALL_INT).size() == 0) {
                ArrayList<Book> books = BookDAO.getBooksFromDB(id_book, Constants.SELECT_ALL_STR);
                if (!books.isEmpty() && books.get(0).getAmount() > 0) {
                    ReadingDAO.addReading(id_user, id_book);
                    BookDAO.takeBook(id_book);
                    answer = new Answer(true, "message");
                } else {
                    answer = new Answer(false, "no such book");
                }
            } else {
                answer = new Answer(false, "you're already reading one");
            }
            String json_answer = new Gson().toJson(answer);
            resp.getWriter().write(json_answer);
            System.out.println(json_answer);
        }
            break;
        case Action.RETURN_BOOK: {
            int id_user = act.get("id_user").getAsInt();
            int id_book = act.get("id_book").getAsInt();
            ReadingDAO.deleteReading(id_user, id_book);
            BookDAO.returnBook(id_book);
        }
            break;
        case Action.GET_READING_BOOK: {
            int id_user = act.get("id_user").getAsInt();
            ArrayList<Reading> readings = ReadingDAO.getReadings(id_user, Constants.SELECT_ALL_INT);
            if (readings.size() != 0) {
                String json_readings = new Gson().toJson(readings.get(0));
                resp.getWriter().write(json_readings);
                System.out.println(json_readings);
            } else {
                Answer answer = new Answer(false, "No readings");
                String json_answer = new Gson().toJson(answer);
                resp.getWriter().write(json_answer);
            }
        }
            break;
        case Action.UNREQUEST_BOOK: {
            int id_user = act.get("id_user").getAsInt();
            int id_book = act.get("id_book").getAsInt();
            RequestBookDAO.deleteRequest(id_user, id_book);
        }
            break;
        case Action.TAKE_HOME: {
            int id_user = act.get("id_user").getAsInt();
            int id_book = act.get("id_book").getAsInt();
            Answer answer;
            if (ReadingDAO.getReadings(id_user, Constants.SELECT_ALL_INT).size() != 0) {
                answer = new Answer(false, "You are reading book rn");
            } else {
                ArrayList<RequestBook> reqs = RequestBookDAO.getBookRequests(id_user, id_book);
                if (reqs.size() == 0) {
                    answer = new Answer(false, "There was no request");
                } else {
                    RequestBook req_book = reqs.get(0);
                    if (!req_book.isAccepted()) {
                        answer = new Answer(false, "Not accepted");
                    } else {
                        ReadingDAO.addReading(id_user, id_book);
                        RequestBookDAO.deleteRequest(id_user, id_book);
                        BookDAO.takeBook(id_book);
                        answer = new Answer(true, "Success");
                    }
                }
            }
            String json_answer = new Gson().toJson(answer);
            resp.getWriter().write(json_answer);
        }
        }
    }
}
