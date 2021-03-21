package com.univ.webService.DAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.Reading;
import com.univ.webService.dataModel.RequestBook;
import com.univ.webService.servlet.Constants;

public class ReadingDAO {
    static public ArrayList<Reading> getReadings(int id_user, int id_book) {
        ArrayList<Reading> reads = new ArrayList<>();
        try {
            Connection connection = DataConnection.getDBConnection();
            final String sqlQuery = String.format("SELECT * FROM reading WHERE %s AND %s",
                    id_user == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_user = " + id_user,
                    id_book == Constants.SELECT_ALL_INT ? "CAST(id_user as TEXT) LIKE '%'" : "id_book = " + id_book);
            PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                    Reading reading = new Reading(rs.getInt("id_user"), rs.getInt("id_book"));
                reads.add(reading);
            }
            connection.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return reads;
    }

    static public boolean addReading(int id_user, int id_book) {
        try {
            if (getReadings(id_user, id_book).size() != 0) {
                return false;
            }
            Connection connection = DataConnection.getDBConnection();
            String sql_query = String.format("INSERT INTO reading (id_user, id_book) VALUES(%s, %s)",
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

    static public boolean deleteReading(int id_user, int id_book) {
        try {
            if (getReadings(id_user, id_book).size() == 0) {
                return false;
            }
            Connection connection = DataConnection.getDBConnection();
            String sql_query = String.format("DELETE FROM reading WHERE %s AND %s",
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
        System.out.println(getReadings(1, -1).get(0).getBook_id());
    }
}
