package com.univ.webService.DAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Book;
import com.univ.webService.servlet.Constants;

public class BookDAO {
    static public ArrayList<Book> getBooksFromDB(int id, String name) {
        ArrayList<Book> books = new ArrayList<>();
        try {
            Connection connection = DataConnection.getDBConnection();

            final String sqlQuery = String.format("SELECT * FROM books WHERE %s AND name LIKE %s",
                    id == Constants.SELECT_ALL_INT ? "CAST(id as TEXT) LIKE '%'" : ("id = " + id),
                    name == Constants.SELECT_ALL_STR ? "'%'" : "'" + name + "'");
            PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
            ResultSet rs = pstmt.executeQuery();

            while (rs.next()) {
                Book book = new Book(rs.getInt("id"), rs.getString("name"), rs.getInt("amount"),
                        rs.getInt("total_amount"));
                books.add(book);
            }
            connection.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return books;
    }

    static public boolean takeBook(int id_book) {
        boolean book_taken = false;
        Connection connection;
        try {
            connection = DataConnection.getDBConnection();
            final String sqlSelect = String.format("SELECT amount FROM books WHERE id = %s", id_book);
            PreparedStatement pstmt = connection.prepareStatement(sqlSelect);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                int amount = rs.getInt("amount");
                if (amount != 0) {
                    --amount;
                    String sqlUpdate = String.format("UPDATE books SET amount = %s WHERE id = %s", amount, id_book);
                    PreparedStatement st = connection.prepareStatement(sqlUpdate);
                    st.executeUpdate();
                    st.close();
                    book_taken = true;
                }
            }
            connection.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return book_taken;
    }

    static public boolean returnBook(int id){
        boolean book_returned = false;
        Connection connection;
        try {
            connection = DataConnection.getDBConnection();
            final String sqlSelect = String.format("SELECT amount, total_amount FROM books WHERE id = %s", id);
            PreparedStatement pstmt = connection.prepareStatement(sqlSelect);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                int amount = rs.getInt("amount");
                int total_amount = rs.getInt("total_amount");
                if (amount < total_amount) {
                    ++amount;
                    String sqlUpdate = String.format("UPDATE books SET amount = %s WHERE id = %s", amount, id);
                    PreparedStatement st = connection.prepareStatement(sqlUpdate);
                    st.executeUpdate();
                    st.close();
                    book_returned = true;
                }
            }
            connection.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return book_returned;
    }

    public static void main(String[] args) {
        // try {
        // ArrayList<Book> books = getBooksFromDB(1, "");
        // for (Book book : books) {
        // System.out.println(book.getName());
        // }
        // // boolean wow = takeBook(2);
        // // System.out.println(wow);
        // // wow = returnBook(2);
        // // System.out.println(wow);
        // // returnBook(1);
        // } catch (SQLException e) {
        // // TODO Auto-generated catch block
        // e.printStackTrace();
        // }
    }
}
