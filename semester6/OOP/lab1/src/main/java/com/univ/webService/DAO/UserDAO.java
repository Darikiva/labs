package com.univ.webService.DAO;

import com.univ.webService.dataConnection.DataConnection;
import com.univ.webService.dataModel.User;
import com.univ.webService.servlet.Constants;

import java.sql.*;
import java.util.ArrayList;

public class UserDAO {
    static public ArrayList<User> getUserFromDB(int id, String login, String password, int isAdmin) throws SQLException {
        ArrayList<User> users = new ArrayList<>();
        Connection connection = DataConnection.getDBConnection();

        final String sqlQuery =
                String.format(
                        "SELECT * FROM users WHERE %s AND login %s AND password %s AND %s",
                        id == Constants.SELECT_ALL_INT ? "CAST(id as TEXT) LIKE '%'" : "id = " + id,
                        login.equals(Constants.SELECT_ALL_STR) ? "LIKE '%'" : "= '" + login + "'",
                        password.equals(Constants.SELECT_ALL_STR) ? "LIKE '%'" : "= '" + password + "'",
                        isAdmin == Constants.SELECT_ALL_INT ? "CAST(admin as TEXT) LIKE '%'" : ("admin = " + (isAdmin != 0 ? true: false))
                );
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        ResultSet rs = pstmt.executeQuery();

        while (rs.next()) {
            User user = new User(rs.getInt("id"), rs.getString("name"), rs.getString("surname"),
                    rs.getString("login"), rs.getString("password"), rs.getBoolean("admin"));
            users.add(user);
        }
        connection.close();
        return users;
    }

    public static void main(String[] args) {
        try {
            ArrayList<User> users = getUserFromDB(Constants.SELECT_ALL_INT, Constants.SELECT_ALL_STR, Constants.SELECT_ALL_STR, Constants.SELECT_ALL_INT);
            for (User user: users) {
                System.out.println(user.getName());
            }
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }
}
