package com.univ.webService.DAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.RequestBook;
import com.univ.webService.servlet.Constants;

public class RequestBookDAO {
    static public ArrayList<RequestBook> getBookRequests(int id_user, int id_book) {
        ArrayList<RequestBook> reqs = new ArrayList<>();
        try {
            Connection connection = DataConnection.getDBConnection();
            final String sqlQuery = String.format("SELECT * FROM mediator WHERE %s AND %s",
                    id_user == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_user = " + id_user,
                    id_book == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_book = " + id_book);
            PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                RequestBook book_request = new RequestBook(rs.getInt("id_user"), rs.getInt("id_book"),
                        rs.getBoolean("accepted"));
                reqs.add(book_request);
            }
            connection.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return reqs;
    }

    static public boolean addRequest(int id_user, int id_book) {
        try {
            if (getBookRequests(id_user, id_book).size() != 0) {
                return false;
            }
            Connection connection = DataConnection.getDBConnection();
            String sql_query = String.format("INSERT INTO mediator (id_user, id_book, accepted) VALUES(%s, %s, %s)",
                    id_user, id_book, false);
            PreparedStatement pstmt = connection.prepareStatement(sql_query);
            pstmt.executeUpdate();
            connection.close();
            return true;
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return false;
        }
    }

    static public boolean deleteRequest(int id_user, int id_book) {
        try {
            if (getBookRequests(id_user, id_book).size() == 0) {
                return false;
            }
            Connection connection = DataConnection.getDBConnection();
            String sql_query = String.format("DELETE FROM mediator WHERE %s AND %s",
                    id_user == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_user = " + id_user,
                    id_book == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_book = " + id_book);
            PreparedStatement pstmt = connection.prepareStatement(sql_query);
            pstmt.executeUpdate();
            connection.close();
            return true;
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return false;
        }
    }

    static public boolean acceptRequest(int id_user, int id_book) {
        try {
            if (getBookRequests(id_user, id_book).size() == 0) {
                return false;
            }
            Connection connection = DataConnection.getDBConnection();
            String sql_query = String.format("UPDATE mediator SET accepted = 'true' WHERE %s AND %s",
                    id_user == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_user = " + id_user,
                    id_book == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_book = " + id_book);
            PreparedStatement pstmt = connection.prepareStatement(sql_query);
            pstmt.executeUpdate();
            connection.close();
            return true;
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        // addRequest(1, 1);
        // addRequest(1, 2);
        deleteRequest(1, 2);
        // System.out.println(acceptRequest(1, -1));
        // deleteRequest(1, -1);
    }
}
